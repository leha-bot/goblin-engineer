#pragma once

#include <cstdint>
#include <iostream>
#include <queue>
#include <unordered_map>

#include <goblin-engineer/forward.hpp>

#include <actor-zeta/actor/basic_actor.hpp>

namespace goblin_engineer {

    using actor_zeta::actor::basic_async_actor;

    struct abstract_service: public basic_async_actor {

        abstract_service(goblin_engineer::context_t *,const std::string& );

        virtual ~abstract_service();

        static constexpr bool in_plugin = false;

        virtual void startup(goblin_engineer::context_t *) = 0;

        virtual void shutdown() = 0;

        ////service_state state_;
    };

}

