#pragma once

#include <cstdint>
#include <iostream>
#include <queue>
#include <unordered_map>

#include <actor-zeta/actor/local_actor.hpp>
#include <actor-zeta/messaging/message.hpp>

#include <goblin-engineer/context.hpp>

namespace goblin_engineer {

    using actor_zeta::messaging::message;

    using sync_actor = actor_zeta::actor::local_actor;

    struct data_provider : public sync_actor {

        data_provider(goblin_engineer::context_t *context,  const std::string &name);

        virtual ~data_provider();

        virtual void startup(goblin_engineer::context_t *) = 0;

        virtual void shutdown() = 0;

        bool send(actor_zeta::messaging::message &&, actor_zeta::executor::execution_device *) override;

        void launch(actor_zeta::executor::execution_device *, bool) override;

        bool send(message &&) override;

    };

}

