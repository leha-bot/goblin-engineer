#ifndef ABSTRACT_PLUGIN_HPP
#define ABSTRACT_PLUGIN_HPP

#include <cstdint>

#include <yaml-cpp/yaml.h>
#include <actor-zeta/actor/abstract_actor.hpp>

#include "forward.hpp"

namespace goblin_engineer {

    struct abstract_plugin {

        virtual void startup(const YAML::Node &)                            = 0;

        virtual void shutdown()                                             = 0;

        virtual void initialization(context_t *)                            = 0;

        virtual metadata_t* metadata() const                                = 0;

        virtual result call(const std::string &, virtual_args &&)           = 0;

        virtual ~abstract_plugin()                                          = default;
    };

    struct abstract_plugin_async:
            public abstract_plugin,
            public actor_zeta::actor::abstract_actor {

        virtual ~abstract_plugin_async()                                    = default;
    };


    struct abstract_plugin_sync: public abstract_plugin {

        virtual ~abstract_plugin_sync()                                     = default;
    };

}
#endif
