#include <goblin-engineer/abstract_service.hpp>

#include <cassert>

#include <goblin-engineer/metadata.hpp>
#include <goblin-engineer/context.hpp>

namespace goblin_engineer {

    abstract_service::abstract_service(goblin_engineer::context_t *context,const std::string& name): basic_async_actor(context->env(),name)/*,state_(service_state::initialized)*/{}

    abstract_service::~abstract_service() = default;
}

