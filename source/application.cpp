#include <unordered_map>
#include <vector>
#include <iostream>

#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/filesystem.hpp>
#include <boost/asio.hpp>

#include "goblin-engineer/application.hpp"
#include "goblin-engineer/plugin.hpp"
#include "goblin-engineer/metadata.hpp"

namespace goblin_engineer {

    inline std::string name(abstract_plugin *ptr) {
        std::string tmp;
        tmp = ptr->metadata()->name;
        return tmp;
    }

    struct application::impl final {
        impl() :
            io_serv(new boost::asio::io_service),
            background_(new boost::thread_group) {
        }

        ~impl() = default;

        void add_plugin(abstract_plugin *plugin) {
            auto size = storage_plugin.size();
            storage_plugin.emplace_back(plugin);
            mapper.emplace(name(plugin), size);
            state_plugin.emplace_back(size);
        }

        plugin& get_plugin(std::size_t index) {
            return storage_plugin.at(index);
        }

        plugin& get_plugin(const std::string __name__) {
            auto index = mapper.find(__name__);
            return storage_plugin.at(index->second);
        }

        state_t state(std::size_t index) const {
            return storage_plugin.at(index).state();
        }

        result invoke(const std::string &name_space, const std::string method, virtual_args &&args) {
            return get_plugin(name_space).call(method, std::forward<virtual_args>(args));
        }

        std::vector<std::size_t> &current_state() {
            return state_plugin;
        }

        boost::asio::io_service *main_loop() {
            return io_serv.get();
        }

        boost::thread_group &background() const {
            return *background_.get();
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

    private:

        std::unique_ptr<boost::asio::io_service> io_serv;
        std::unique_ptr<boost::thread_group>     background_;


        /// plugin
        std::vector<plugin> storage_plugin;
        std::unordered_map<std::string, std::size_t> mapper;
        std::vector<std::size_t> state_plugin;
        /// plugin

    };

    void application::shutdown() {

        for (const auto &i:pimpl->current_state()) {
            if (pimpl->state(i) == state_t::started) {
                pimpl->get_plugin(i).shutdown();
            }
        }

        pimpl->main_loop()->stop();

    }

    void application::startup() {

        for (const auto &i:pimpl->current_state()) {
            if (pimpl->state(i) == state_t::initialized) {
                pimpl->get_plugin(i).startup(pimpl->configuration());
            }
        }

        pimpl->main_loop()->run();

        shutdown();
    }

    void application::initialize() {

        for(auto&i:pimpl->signal) {
            std::shared_ptr<boost::asio::signal_set> sigint_set(new boost::asio::signal_set(main_loop(), i));
            sigint_set->async_wait(
                    [sigint_set, this](const boost::system::error_code &err, int num) {
                        shutdown();
                        sigint_set->cancel();
                    }
            );
        }

        for(const auto&i:pimpl->plgins_initialize) {
            plugin& plugin = pimpl->get_plugin(i);
            if (plugin.state() == state_t::registered) {
                plugin.initialization(context());
            }
        }

    }

    application::application() : pimpl(new impl) {}

    void application::add_plugin(abstract_plugin *plugin) {
        pimpl->add_plugin(plugin);
    }

    application::~application() {
        std::cerr << "~goblin-engineer" << std::endl;
    }

    result application::call(const std::string &name_space, const std::string &method, virtual_args &&args) {
        return pimpl->invoke(name_space, method, std::forward<virtual_args>(args));
    }

    context_t *application::context() {
        return static_cast<context_t*>(this);
    }

    boost::asio::io_service &application::main_loop() const  {
        return *pimpl->main_loop();
    }

    boost::thread_group &application::background() const {
        return pimpl->background();
    }

    void application::load_config(configuration&&f) {
        pimpl->configuration_    = YAML::LoadFile(f.config_path);
        pimpl->plgins_initialize = f.plugins; //TODO Boost.DLL
        pimpl->data_dir          = f.data_dir;
        pimpl->plugins_dir       = f.plugins_dir;
        pimpl->signal            = f.signal;
    }
}