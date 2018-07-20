#include <goblin-engineer/dynamic_environment.hpp>

#include <unordered_map>
#include <vector>
#include <iostream>

#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/filesystem.hpp>
#include <boost/asio.hpp>

#include <actor-zeta/environment/cooperation.hpp>
#include <actor-zeta/executor/abstract_coordinator.hpp>
#include <actor-zeta/executor/coordinator.hpp>
#include <actor-zeta/executor/policy/work_sharing.hpp>


#include <goblin-engineer/metadata.hpp>
#include <goblin-engineer/service.hpp>
#include <goblin-engineer/plugin.hpp>
#include <goblin-engineer/abstract_service.hpp>

namespace goblin_engineer {

    inline std::string name_service(abstract_service *ptr) {
        std::string tmp;
        std::unique_ptr<metadata_service> metadata(new metadata_service);
        ptr->metadata(metadata.get());
        tmp = metadata->name;
        return tmp;
    }


    inline std::string name_plugin(abstract_plugin *ptr) {
        std::string tmp;
        std::unique_ptr<metadata_plugin> metadata(new metadata_plugin);
        ptr->metadata(metadata.get());
        tmp = metadata->name;
        return tmp;
    }

    struct dynamic_environment::impl final {
        impl() :
            coordinator_(new actor_zeta::executor::coordinator<actor_zeta::executor::work_sharing>(1, 1000)),
            io_serv(new boost::asio::io_service),
            background_(new boost::thread_group){
        }

        ~impl() = default;

        auto add_plugin(abstract_plugin *plugin_ptr) -> void {
            auto size = storage_plugin.size();
            storage_plugin.emplace_back(plugin_ptr);
            mapper.emplace(name_plugin(plugin_ptr), size);
            state_plugin.emplace_back(size);
        }

        auto add_service(abstract_service_managed *service_ptr) -> service& {
            auto g = cooperation_.created_group(service_ptr->unpack());
            service_ptr->pack(std::move(g));
            //return service(service_ptr);

        }

        auto add_service(abstract_service_unmanaged *unmanaged_service) -> service& {
            auto result = unmanaged_services.emplace(name_service(unmanaged_service),unmanaged_service);
            return result.first->second;
        }

        auto get_plugin(std::size_t index) -> plugin& {
            return storage_plugin.at(index);
        }

        auto get_plugin(const std::string& __name__) -> plugin& {
            auto index = mapper.find(__name__);
            return storage_plugin.at(index->second);
        }

        plugin_state state(std::size_t index) const {
            return storage_plugin.at(index).state();
        }

        std::vector<std::size_t> &current_state() {
            return state_plugin;
        }

        boost::asio::io_service *main_loop() {
            return io_serv.get();
        }

        boost::thread_group &background() const {
            return *background_;
        }

        YAML::Node &configuration() {
            return configuration_;
        }

        ///Config
        YAML::Node                               configuration_;
        std::set<std::string>                    plgins_initialize;
        boost::filesystem::path                  data_dir;
        boost::filesystem::path                  plugins_dir;
        std::set<std::size_t>                    signal;
        ///Config

        actor_zeta::environment::cooperation cooperation_;
        actor_zeta::executor::abstract_coordinator* coordinator_;


        ///service
        std::unordered_map<std::string, service>  unmanaged_services;
        ///service

    private:



        /// plugin
        std::vector<plugin> storage_plugin;
        std::unordered_map<std::string, std::size_t> mapper;
        std::vector<std::size_t> state_plugin;
        /// plugin

        std::unique_ptr<boost::asio::io_service> io_serv;
        std::unique_ptr<boost::thread_group>     background_;

    };

    void dynamic_environment::shutdown() {

        for( auto&i:pimpl->unmanaged_services){
            i.second.shutdown();
        }

        for (const auto &i:pimpl->current_state()) {
            if (pimpl->state(i) == plugin_state ::started) {
                pimpl->get_plugin(i).shutdown();
            }
        }

        pimpl->main_loop()->stop();

    }

    void dynamic_environment::startup() {

        for( auto&i:pimpl->unmanaged_services){
            i.second.startup(pimpl->configuration());
        }

        for (const auto &i:pimpl->current_state()) {
            if (pimpl->state(i) == plugin_state ::initialized) {
                pimpl->get_plugin(i).startup(pimpl->configuration());
            }
        }

        pimpl->main_loop()->run();

        shutdown();
    }

    void dynamic_environment::initialize() {

        std::shared_ptr<boost::asio::signal_set> sigint_set(new boost::asio::signal_set(main_loop(), SIGINT,SIGTERM));
        sigint_set->async_wait(
                [sigint_set, this](const boost::system::error_code &/*err*/, int /*num*/) {
                    shutdown();
                    sigint_set->cancel();
                }
        );

        if(!pimpl->signal.empty()){
            for(auto&i:pimpl->signal) {
                std::shared_ptr<boost::asio::signal_set> sigint_set(new boost::asio::signal_set(main_loop(), i));
                sigint_set->async_wait(
                        [sigint_set, this](const boost::system::error_code &/*err*/, int /*num*/) {
                            shutdown();
                            sigint_set->cancel();
                        }
                );
            }
        }

        for( auto&i:pimpl->unmanaged_services){
            i.second.initialization(context());
        }

        for(const auto&i:pimpl->plgins_initialize) {
            auto& plugin = pimpl->get_plugin(i);
            if (plugin.state() == plugin_state ::registered) {
                plugin.initialization(context());
            }
        }

    }

    dynamic_environment::dynamic_environment() : pimpl(new impl) {
    }


    dynamic_environment::~dynamic_environment() {
        pimpl->background().join_all();
        pimpl->main_loop()->stopped();
        std::cerr << "~goblin-engineer" << std::endl;
    }



    context_t *dynamic_environment::context() {
        return static_cast<context_t*>(this);
    }

    boost::asio::io_service &dynamic_environment::main_loop() const  {
        return *pimpl->main_loop();
    }

    boost::thread_group &dynamic_environment::background() const {
        return pimpl->background();
    }

    int dynamic_environment::start() {
        manager_execution_device().start();
        return 0;
    }

    actor_zeta::executor::abstract_coordinator &dynamic_environment::manager_execution_device() {
        return *pimpl->coordinator_;
    }

    actor_zeta::environment::cooperation &dynamic_environment::manager_group() {
        return  pimpl->cooperation_;
    }

    auto dynamic_environment::add_plugin(abstract_plugin * plugin_ptr) -> void {
        return pimpl->add_plugin(plugin_ptr);
    }

    void dynamic_environment::load_config(configuration&&f) {
        pimpl->configuration_    = YAML::LoadFile(f.config_path);
        pimpl->plgins_initialize = f.plugins; //TODO Boost.DLL
        pimpl->data_dir          = f.data_dir;
        pimpl->plugins_dir       = f.plugins_dir;
        pimpl->signal            = f.signal;
    }

    auto dynamic_environment::add_service(abstract_service_unmanaged *service_ptr) -> service & {
        return pimpl->add_service(service_ptr);
    }

    auto dynamic_environment::add_service(abstract_service_managed *service_ptr) -> service & {
       return pimpl->add_service(service_ptr);
    }

}