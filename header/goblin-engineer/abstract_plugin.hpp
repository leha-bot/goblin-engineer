#pragma once
#include <cstdint>

#include <yaml-cpp/yaml.h>
#include <goblin-engineer/message.hpp>
#include <actor-zeta/environment/abstract_group.hpp>

namespace goblin_engineer {
    /// container service
    struct abstract_plugin {
        using actor_zeta::environment::abstract_group;

        virtual void initialization(context_t *)                            = 0;

        virtual void startup(const YAML::Node &)                            = 0;

        virtual void shutdown()                                             = 0;

        virtual void metadata(metadata_plugin*) const                       = 0;

        virtual ~abstract_plugin()                                          = default;
    };

}

