#ifndef PLUGIN_CONTEXT_HPP
#define PLUGIN_CONTEXT_HPP

#include "forward.hpp"

#include <boost/asio.hpp>
#include <boost/thread.hpp>

namespace goblin_engineer {

    struct context_t {

        virtual result call(const std::string &name_space, const std::string &method, virtual_args &&args) = 0;

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

#endif //PLUGIN_CONTEXT_HPP
