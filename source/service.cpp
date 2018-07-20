#include <iostream>
#include <goblin-engineer/service.hpp>

#include "goblin-engineer/service.hpp"
#include "goblin-engineer/abstract_service.hpp"
#include "goblin-engineer/metadata.hpp"
namespace goblin_engineer {
    inline std::string name(abstract_service* ptr){
        std::string tmp;
        std::unique_ptr<metadata_service> metadata(new metadata_service);
        ptr->metadata(metadata.get());
        tmp = metadata->name;
        return tmp;
    }

    void service::state(service_state state_) {
        this->state_ = state_;
    }

    service_state service::state() const {
        return state_;
    }

    service::service(abstract_service *ptr) :
            state_(service_state::registered),
            plugin_(ptr){
    }
    
    void service::startup(const YAML::Node &options) {
        std::cerr << "startup service: " << name(self()) << std::endl;
        if (state() == service_state::initialized) {
            state(service_state::started);
            return self()->startup(options);
        } else {
            std::cerr << "error startup  service: " << name(self()) << std::endl;
        }
    }

    void service::initialization(context_t *context) {
        std::cerr << "initialization service: " << name(self()) << std::endl;
        if (state() == service_state::registered) {
            state(service_state::initialized);
            return self()->initialization(context);
        } else {
            std::cerr << "error initialization service: " << name(self()) << std::endl;
        }
    }

    void service::shutdown() {
        std::cerr << "shutdown service:" << name(self()) << std::endl;
        if (state() == service_state::started) {
            state(service_state::stopped);
            return self()->shutdown();
        } else {
            std::cerr << "error shutdown service:" << name(self()) << std::endl;
        }

    }

    void service::metadata(metadata_service *metadata) const {
        self()->metadata(metadata);
    }

    auto service::operator->() const noexcept -> abstract_service * {
        return plugin_.get();
    }

    auto service::operator*() const noexcept -> abstract_service & {
        return *plugin_;
    }

    auto service::operator->() noexcept -> abstract_service * {
        return plugin_.get();
    }

    auto service::operator*() noexcept -> abstract_service & {
        return *plugin_;
    }

    auto service::get() noexcept -> abstract_service * {
        return plugin_.get();
    }

    auto service::get() const noexcept -> abstract_service * {
        return plugin_.get();
    }
}