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

    bool abstract_service_managed::send(msg &&) {
        ///group_->send(s)
    }

    void abstract_service_unmanaged::join(service &s) {
        auto *raw = s.get();
        assert(raw->managed == false);
        auto* meta_data = new metadata_service;
        s.metadata(meta_data);
        services.emplace(meta_data->name,s.get());

    }

    bool abstract_service_unmanaged::send(msg &&message) {
        bool result;
        auto it = method_table.find(message.method);
        if (it != method_table.end()) {
            it->second(std::move(message));
            result = true;
        } else {
            result = false;
        }

        return result;

    }

    void abstract_service_unmanaged::input(service &s) {
        std::unique_ptr<metadata_service> service_(new metadata_service);
        s.metadata(service_.get());
        join(s);
        input_ = service_->name;
    }

    void abstract_service_unmanaged::output(service &s) {
        std::unique_ptr<metadata_service> service_(new metadata_service);
        s.metadata(service_.get());
        join(s);
        output_ = service_->name;
    }

    auto abstract_service_unmanaged::input() const -> const std::string & {
        return input_;
    }

    auto abstract_service_unmanaged::output() const -> const std::string & {
        return output_;
    }

    auto abstract_service_unmanaged::get_service(const std::string& name) -> service & {
        return services.at(name);
    }

    pipe *abstract_service::to_pipe() {
        return static_cast<pipe *>(this);
    }

    abstract_service::abstract_service() :state_(service_state::initialized){}
}

