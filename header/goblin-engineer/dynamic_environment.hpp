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

        dynamic_environment();

        ~dynamic_environment();

        auto add_service(abstract_service_unmanaged*) -> service&;

        auto add_service(abstract_service_managed*) -> service&;

        auto add_plugin(abstract_plugin *) -> void;

        void load_config(configuration&&);

        void initialize();

        void startup();

        void shutdown();

    private:

        int start() override ;

        actor_zeta::executor::abstract_coordinator & manager_execution_device() override ;

        actor_zeta::environment::cooperation & manager_group() override ;

        context_t *context();

        boost::asio::io_service& main_loop() const override;

        boost::thread_group& background() const override;

        struct impl;

        std::unique_ptr<impl> pimpl;
    };

    template<typename SERVICE, typename ...Args>
    auto add_service(dynamic_environment &app, Args &&...args) -> service& {
        return app.add_service(new SERVICE(std::forward<Args>(args)...));
    }

    template<typename SERVICE>
    auto add_service(dynamic_environment &app) -> service& {
        return app.add_service(new SERVICE());
    }

    inline auto add_plugin(dynamic_environment &app, abstract_plugin* plugin ) -> void {
        app.add_plugin(plugin);
    }

}

