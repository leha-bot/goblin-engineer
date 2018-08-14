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
        service_.get()->state_ = state_;
    }

    service_state service::state() const {
        return service_.get()->state_;
    }

    service::service(abstract_service *ptr) :
            service_(ptr){
    }
    
    void service::startup(context_t *context) {
        std::cerr << "startup service: " << name(self()) << std::endl;
        if (state() == service_state::initialized) {
            state(service_state::started);
            return self()->startup(context);
        } else {
            std::cerr << "error startup  service: " << name(self()) << std::endl;
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
        return service_.get();
    }

    auto service::operator*() const noexcept -> abstract_service & {
        return *service_;
    }

    auto service::operator->() noexcept -> abstract_service * {
        return service_.get();
    }

    auto service::operator*() noexcept -> abstract_service & {
        return *service_;
    }

    auto service::get() noexcept -> abstract_service * {
        return service_.get();
    }

    auto service::get() const noexcept -> abstract_service * {
        return service_.get();
    }

    auto service::self() -> abstract_service * {
        return service_.get();
    }

    auto service::self() const -> const abstract_service * {
        return service_.get();
    }
}