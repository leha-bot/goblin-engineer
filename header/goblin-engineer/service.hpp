#pragma once

#include <string>
#include <atomic>
#include <memory>
#include <goblin-engineer/forward.hpp>


namespace goblin_engineer {

    class service final {
    public:

        service() = default;

        service(service&&) = default;

        service&operator=(service&&) = default;

        service(abstract_service*);

        ~service() = default;

        void startup(context_t *);

        void shutdown();

        void metadata(metadata_service *) const;

        void state(service_state);

        auto operator->() const noexcept -> abstract_service *;

        auto operator*() const noexcept -> abstract_service &;

        auto operator->() noexcept -> abstract_service *;

        auto operator*() noexcept -> abstract_service &;

        auto get() noexcept -> abstract_service *;

        auto get() const noexcept -> abstract_service *;

        service_state state() const;

    private:
        bool load_metadata;
        std::unique_ptr<metadata_service> metadata_;
        std::unique_ptr<abstract_service> service_;

        auto self() -> abstract_service *;

        auto self() const -> const abstract_service *;

    };

}
