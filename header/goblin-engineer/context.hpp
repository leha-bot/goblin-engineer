#pragma once

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include <goblin-engineer/forward.hpp>
#include <goblin-engineer/dynamic.hpp>

#include <actor-zeta/environment/abstract_environment.hpp>

namespace goblin_engineer {

    struct context_t {

        virtual auto env() -> actor_zeta::environment::abstract_environment * = 0;

        virtual auto  config() const -> dynamic_config&    = 0;

        virtual boost::asio::io_service &main_loop() const = 0;

        virtual boost::thread_group &background()    const = 0;

        virtual ~context_t() = default;

    };

}
