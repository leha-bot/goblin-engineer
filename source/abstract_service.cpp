#include <goblin-engineer/abstract_service.hpp>

#include <cassert>

#include <goblin-engineer/metadata.hpp>

namespace goblin_engineer {


    auto abstract_service_managed::unpack() -> abstract_actor * {
        return actor.release();
    }

    auto abstract_service_managed::pack(actor_zeta::environment::group &&group_) -> void {
        this->group_ = std::move(group_);
    }

    void abstract_service_managed::join(service &s) {
        auto *raw = s.get();
        assert(raw->managed == true);
        auto *srvce = static_cast<abstract_service_managed *>(s.get());

        group()->join(srvce->group());

    }

    auto abstract_service_managed::group() -> actor_zeta::environment::group & {
        return group_;
    }

    bool abstract_service_managed::send(message &&) {
        ///group_->send(s)
        ///TODO implementation
        return false;
    }

    abstract_service_managed::~abstract_service_managed() = default;

    void abstract_service_unmanaged::join(service &s) {
        auto *raw = s.get();
        assert(raw->managed == false);
        auto* meta_data = new metadata_service;
        s.metadata(meta_data);
        services.emplace(meta_data->name,s.get());

    }

    bool abstract_service_unmanaged::send(message &&message) {

        bool result;

        auto current_name = name();
        if(message.sender == current_name ) {
            auto it = method_table.find(message.method);
            if (it != method_table.end()) {
                it->second(std::move(message));
                result = true;
            } else {
                result = false;
            }
        } else {
            auto& service = services.at(message.sender);
            result = service->send(std::move(message));
        }

        return result;

    }

    abstract_service_unmanaged::~abstract_service_unmanaged()  = default;


    pipe *abstract_service::to_pipe() {
        return static_cast<pipe *>(this);
    }

    abstract_service::abstract_service() :state_(service_state::initialized){}

    abstract_service::~abstract_service() = default;
}

