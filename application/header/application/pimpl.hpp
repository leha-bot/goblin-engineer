#ifndef MEMORY_PIMPL_PTR_H
#define MEMORY_PIMPL_PTR_H

#include <cassert>
#include <memory>

#if   __cplusplus >= 201402L
using std::make_unique
#elif __cplusplus >= 201103L
namespace std {
template<typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args &&...args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
}
#endif

namespace application {
    namespace utils {

        template<class T>
        class pimpl_ptr {
        public:
            using ElementType = typename std::unique_ptr<T>::element_type;

            pimpl_ptr() : p_(std::make_unique<T>()) {
                static_assert(sizeof(T) > 0, "Probably, you forgot to declare constructor explicitly");
            }

            explicit pimpl_ptr(std::unique_ptr<T> &&p) noexcept: p_(std::move(p)) { assert(p_ != nullptr); }

            pimpl_ptr(pimpl_ptr &&) noexcept = default;

            pimpl_ptr &operator=(pimpl_ptr &&) noexcept = default;

            pimpl_ptr(const pimpl_ptr &) noexcept = delete;

            pimpl_ptr &operator=(const pimpl_ptr &) noexcept = delete;

            ~pimpl_ptr() {
                static_assert(sizeof(T) > 0, "Probably, you forgot to declare destructor explicitly");
            }

            const ElementType *get() const noexcept { return p_.get(); }

            const ElementType *operator->() const noexcept { return get(); }

            const ElementType &operator*() const noexcept { return *get(); }

            explicit operator const ElementType *() const noexcept { return get(); }

            ElementType *get() noexcept { return p_.get(); }

            ElementType *operator->() noexcept { return get(); }

            ElementType &operator*() noexcept { return *get(); }

            explicit operator ElementType *() noexcept { return get(); }

        private:
            std::unique_ptr<T> p_;
        };

    } // namespace utils
}

#endif // MEMORY_PIMPL_PTR_H