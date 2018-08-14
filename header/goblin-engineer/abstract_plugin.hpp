#pragma once
#include <cstdint>

#include <goblin-engineer/context.hpp>
#include <goblin-engineer/metadata.hpp>

namespace goblin_engineer {
    /// container service
    struct abstract_plugin {

        virtual void initialization()                 = 0;

        virtual void startup(context_t *)             = 0;

        virtual void shutdown()                       = 0;

        virtual void metadata(metadata_plugin*) const = 0;

        virtual ~abstract_plugin()                    = default;
    };

}

