#pragma once

#include <string>
#include <atomic>
#include <yaml-cpp/yaml.h>
#include <goblin-engineer/forward.hpp>


namespace goblin_engineer {

    enum class service_state : char {
        registered,  ///< the service is constructed but doesn't do anything
        initialized, ///< the service has initlaized any state required but is idle
        started,     ///< the service is actively running
        stopped      ///< the service is no longer running
    };

    class service final   {
    public:

        service() = default;

        service(service&&) = default;

        service&operator=(service&&) = default;

        service(abstract_service*);

        ~service() = default;

        void startup(const YAML::Node &options);

        void initialization(context_t *context);

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
        std::atomic_bool load_metadata;
        std::unique_ptr<metadata_service> metadata_;
        service_state state_;

        std::unique_ptr<abstract_service> plugin_;

        inline auto self() -> abstract_service * {
            return plugin_.get();
        }

        inline auto self() const -> const abstract_service * {
            return plugin_.get();
        }
    };


}
