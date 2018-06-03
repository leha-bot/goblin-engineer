#pragma once
#include <cstdint>

#include <yaml-cpp/yaml.h>
#include <actor-zeta/actor/abstract_actor.hpp>
#include <actor-zeta/actor/basic_actor.hpp>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/behavior/behavior.hpp>
#include <actor-zeta/messaging/blocking_mail_queue.hpp>
#include <actor-zeta/actor/broker.hpp>
#include <actor-zeta/environment/abstract_group.hpp>

#include "forward.hpp"

namespace goblin_engineer {

    struct abstract_plugin {
        using actor_zeta::environment::abstract_group;

        virtual void startup(const YAML::Node &)                            = 0;

        virtual void shutdown()                                             = 0;

        virtual void initialization(context_t *)                            = 0;

        virtual metadata_t* metadata() const                                = 0;

        virtual result send(const std::string &, virtual_args &&)           = 0;

        virtual ~abstract_plugin()                                          = default;
    };

    struct abstract_plugin_abstract_group:
            public abstract_plugin,
            public abstract_group {

        virtual ~abstract_plugin_async()                                    = default;
    };

    struct abstract_plugin_sync: public abstract_plugin {

        virtual ~abstract_plugin_sync()                                     = default;
    };

}

