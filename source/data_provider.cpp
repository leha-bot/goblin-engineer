#include <goblin-engineer/data_provider.hpp>
#include <goblin-engineer/context.hpp>
#include <cassert>

namespace goblin_engineer {

    bool data_provider::send(message &&message) {
/*
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
*/
    }

    data_provider::data_provider(goblin_engineer::context_t *context, const std::string &name):sync_actor(context->env(),name){

    }

    bool data_provider::send(actor_zeta::messaging::message &&, actor_zeta::executor::execution_device *) {

    }

    void data_provider::launch(actor_zeta::executor::execution_device *, bool) {

    }

    data_provider::~data_provider()  = default;

}

