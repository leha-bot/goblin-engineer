#pragma once

#include <goblin-engineer/forward.hpp>
#include <goblin-engineer/context.hpp>
#include <goblin-engineer/configuration.hpp>
#include <actor-zeta/environment/environment.hpp>


namespace goblin_engineer {

    class dynamic_environment final :
            public context_t,
            public actor_zeta::environment::abstract_environment {
    public:

        dynamic_environment(configuration&&);

        ~dynamic_environment();

        template <typename SERVICE,typename ...Args>
        auto add_service(Args &&...args) -> service& {
            return add_service(new SERVICE(static_cast<context_t*>(this),std::forward<Args>(args)...));
        }

        auto add_plugin(abstract_plugin *) -> void;

        void initialize();

        void startup();

        void shutdown();

    private:

        auto add_service(abstract_service_unmanaged*) -> service&;

        auto add_service(abstract_service_managed*) -> service&;

        auto  config() const -> dynamic_config& override;

        auto start() -> int override ;

        auto  manager_execution_device() -> actor_zeta::executor::abstract_coordinator & override ;

        auto  manager_group() -> actor_zeta::environment::cooperation & override ;

        auto context() -> context_t *;

        auto  main_loop() const -> boost::asio::io_service& override;

        auto  background() const -> boost::thread_group& override;

        struct impl;

        std::unique_ptr<impl> pimpl;
    };

    inline auto add_plugin(dynamic_environment &app, abstract_plugin* plugin ) -> void {
        app.add_plugin(plugin);
    }

}

