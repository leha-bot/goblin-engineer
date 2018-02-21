#pragma once

#include <functional>
#include "context.hpp"
#include "forward.hpp"
#include "configuration.hp"

namespace goblin_engineer {

    class application final :
            public context_t {
    public:

        application();

        ~application();

        void add_plugin(abstract_plugin *);

        void load_config(configuration&&);

        void initialize();

        void startup();

        void shutdown();

    private:

        context_t *context();

        result call(const std::string &, const std::string &method, virtual_args &&) override;

        boost::asio::io_service& main_loop() const override;

        boost::thread_group& background() const override;

        struct impl;

        std::unique_ptr<impl> pimpl;
    };

    template<typename PLUGIN, typename ...Args>
    void add_plugin(application &app, Args &&...args) {
        app.add_plugin(new PLUGIN(std::forward<Args>(args)...));
    }

    template<typename PLUGIN>
    void add_plugin(application &app) {
        app.add_plugin(new PLUGIN());
    }
}

