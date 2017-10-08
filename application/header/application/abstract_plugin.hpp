#ifndef ABSTRACT_PLUGIN_HPP
#define ABSTRACT_PLUGIN_HPP

#include <cstdint>
#include <string>

#include <boost/program_options/variables_map.hpp>

#include "forward.hpp"

namespace application {

    enum class state_t : uint8_t {
        registered, ///< the plugin is constructed but doesn't do anything
        initialized, ///< the plugin has initlaized any state required but is idle
        started, ///< the plugin is actively running
        stopped ///< the plugin is no longer running
    };

    class abstract_plugin {
    public:
        abstract_plugin();

        virtual void startup(const boost::program_options::variables_map &) = 0;

        virtual void shutdown()                                             = 0;

        virtual void initialization(context_t *)                            = 0;

        virtual std::string name() const                                    = 0;

        virtual result call(const std::string &, virtual_args &&)           = 0;

        virtual ~abstract_plugin() = default;

        void state(state_t state_);

        state_t state() const;

    private:
        state_t state_;
    };
}
#endif
