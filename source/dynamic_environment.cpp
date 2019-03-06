#include <goblin-engineer/dynamic_environment.hpp>

#include <forward_list>
#include <iostream>

#include <actor-zeta/environment/cooperation.hpp>
#include <actor-zeta/executor/coordinator.hpp>
#include <actor-zeta/executor/policy/work_sharing.hpp>

#include <goblin-engineer/dynamic/dynamic.hpp>
#include <goblin-engineer/abstract_service.hpp>
#include <goblin-engineer/data_provider.hpp>
#include <goblin-engineer/abstract_plugin.hpp>


namespace goblin_engineer {

    struct dynamic_environment::impl final {
        impl() :
                coordinator_(new actor_zeta::executor::coordinator<actor_zeta::executor::work_sharing>(1, 1000)),
                io_serv(new boost::asio::io_service),
                background_(new boost::thread_group) {
        }

        ~impl() = default;

        auto main_loop() -> boost::asio::io_service * {
            return io_serv.get();
        }

        auto background() const -> boost::thread_group & {
            return *background_;
        }

        auto configuration() -> dynamic_config & {
            return configuration_;
        }

        dynamic_config configuration_;

        actor_zeta::environment::cooperation cooperation_;
        std::unique_ptr<actor_zeta::executor::abstract_coordinator>coordinator_;
        std::unordered_map<std::string,std::unique_ptr<data_provider> >  data_provider_;

    private:
        std::unique_ptr<boost::asio::io_service> io_serv;
        std::unique_ptr<boost::thread_group> background_;

    };

    void dynamic_environment::shutdown() {

        for (auto &i:pimpl->data_provider_) {
            auto&provider = *i.second.get();
            std::cerr << "shutdown service:" << provider.name() << std::endl;
            provider.shutdown();
        }

        pimpl->main_loop()->stop();

    }

    void dynamic_environment::startup() {

        for (auto &i:pimpl->data_provider_) {
            auto& provider = *(i.second.get());
            std::cerr << "startup service: " << provider.name() << std::endl;
            provider.startup(context());
        }

        start();

        shutdown();
    }

    void dynamic_environment::initialize() {

    }

    dynamic_environment::dynamic_environment(dynamic_config &&f) : pimpl(new impl) {
        pimpl->configuration_ = std::move(f);

        std::shared_ptr<boost::asio::signal_set> sigint_set(new boost::asio::signal_set(main_loop(), SIGINT, SIGTERM));
        sigint_set->async_wait(
                [sigint_set, this](const boost::system::error_code &/*err*/, int /*num*/) {
                    shutdown();
                    sigint_set->cancel();
                }
        );

    }


    dynamic_environment::~dynamic_environment() {
        pimpl->background().join_all();
        pimpl->main_loop()->stopped();
        std::cerr << "~goblin-engineer" << std::endl;
    }

    auto dynamic_environment::context() -> context_t * {
        return static_cast<context_t *>(this);
    }

    boost::asio::io_service &dynamic_environment::main_loop() const {
        return *pimpl->main_loop();
    }

    boost::thread_group &dynamic_environment::background() const {
        return pimpl->background();
    }

    int dynamic_environment::start() {
        manager_execution_device().start();
        return pimpl->main_loop()->run();
    }

    auto dynamic_environment::manager_execution_device() -> actor_zeta::executor::abstract_coordinator & {
        return *pimpl->coordinator_;
    }

    auto dynamic_environment::manager_group() -> actor_zeta::environment::cooperation & {
        return pimpl->cooperation_;
    }

    auto dynamic_environment::add_plugin(abstract_plugin *plugin_ptr) -> void {
        {

            std::unique_ptr<abstract_plugin>_(plugin_ptr);
            auto metadata = std::make_unique<meta_data_plugin>();
            plugin_ptr->meta_data(metadata.get());
            plugin_ptr->initialization(config(),env());
            plugin_ptr->startup(context());

        }
    }

    auto dynamic_environment::add_service(abstract_service *service_ptr) -> service & {
        service_ptr->startup(context());
        return manager_group().created_group(service_ptr);
    }

    auto dynamic_environment::config() const -> dynamic_config & {
        return pimpl->configuration();
    }

    auto dynamic_environment::env() -> goblin_engineer::abstract_environment  * {
        return static_cast<goblin_engineer::abstract_environment  *>(this);
    }

    auto dynamic_environment::add_data_provider(data_provider *ptr ) -> data_provider & {
       auto name_  =  ptr->name();
       pimpl->data_provider_.emplace(name_,ptr);
       return *(pimpl->data_provider_.at(name_).get());
    }

}