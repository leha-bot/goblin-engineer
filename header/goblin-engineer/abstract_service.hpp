#pragma once

#include <goblin-engineer/forward.hpp>
#include <actor-zeta/core.hpp>

namespace goblin_engineer {

    using  actor_zeta::actor::basic_async_actor;

    struct abstract_service : public basic_async_actor {

        template <class Supervisor >
        abstract_service(Supervisor *supervisor, actor_zeta::detail::string_view name) : basic_async_actor(supervisor,name) {}

        ~abstract_service() override = default;
    };


}

