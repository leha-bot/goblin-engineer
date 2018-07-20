#include <goblin-engineer/context.hpp>
namespace goblin_engineer {
   context::context(context_t *ptr) : ptr_(ptr) {}

    context::~context() {
        if (ptr_.get() != nullptr) {
            ptr_.release();
        }
    }

    void context::reset(context_t *ptr) noexcept {
        if (ptr_.get() == nullptr) {
            ptr_.reset(ptr);
        }
    }

    auto context::operator->() const noexcept -> context_t * {
        return ptr_.get();
    }

    auto context::operator*() const noexcept -> context_t & {
        return *ptr_;
    }

    auto context::operator*() noexcept -> context_t & {
        return *ptr_;
    }

    context::operator bool() {
        return static_cast<bool>(ptr_);
    }

    auto context::operator->() noexcept -> context_t * {
        return ptr_.get();
    }
}