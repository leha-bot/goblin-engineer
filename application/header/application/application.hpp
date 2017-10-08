#ifndef PLUGIN_APPLICATION_HPP
#define PLUGIN_APPLICATION_HPP

#include <functional>
#include <boost/smart_ptr/intrusive_ptr.hpp>

#include "pimpl.hpp"
#include "context.hpp"
#include "forward.hpp"
namespace application {

    class application final : public context_t {
    public:

        application(int argc, char **argv);

        ~application();

        void add_plugin(abstract_plugin *);

        void initialize();

        void startup();

        void shutdown();

    private:
        context_t *context();

        result call(const std::string &, const std::string &method, virtual_args &&) override;

        class impl;

        utils::pimpl_ptr<impl> pimpl;
    };

    using application_ptr = boost::intrusive_ptr<application::application>;

    template<typename PLUGIN, typename ...Args>
    void add_plugin(boost::intrusive_ptr<application> app, Args && ...args) {
        app->add_plugin(new PLUGIN(std::forward<Args>(args)...));
    }

    template<typename PLUGIN>
    void add_plugin(boost::intrusive_ptr<application> app) {
        app->add_plugin(new PLUGIN());
    }
}
#endif
