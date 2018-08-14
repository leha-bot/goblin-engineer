#pragma once

#include <goblin-engineer/forward.hpp>
#include <goblin-engineer/dynamic.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <goblin-engineer/dynamic.hpp>

namespace goblin_engineer {

    struct context_t {

        virtual auto  config() const -> dynamic_config&    = 0;

        virtual boost::asio::io_service &main_loop() const = 0;

        virtual boost::thread_group &background()    const = 0;

        virtual ~context_t() = default;

    };

    // semantics smart ptr
    class context final {
    public:
        context() = default;

        context(const context &) = default;

        context &operator=(const context &) = default;

        context(context &&) = default;

        context &operator=(context &&) = default;

        context(context_t *);

        ~context();

        void reset(context_t *) noexcept;

        auto operator->() const noexcept -> context_t *;

        auto operator*() const noexcept -> context_t &;

        auto operator->() noexcept -> context_t *;

        auto operator*() noexcept -> context_t &;

        explicit operator bool();

    private:
        std::unique_ptr<context_t> ptr_;
    };
}
