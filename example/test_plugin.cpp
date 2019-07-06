#include "test_plugin.hpp"

void example_plugin_service::initialization(goblin_engineer::dynamic_config &,actor_zeta::environment::abstract_environment * env) {
    prototype = std::make_unique<example_plugin_actor>(env);
}

void example_plugin_service::startup(goblin_engineer::context_t *) {

}


void example_plugin_service::meta_data(goblin_engineer::meta_data_plugin *) const {

}

namespace test {

    auto load_plugin() -> goblin_engineer::abstract_plugin * {
        return new example_plugin_service;
    }

}

///BOOST_DLL_AUTO_ALIAS()
BOOST_DLL_ALIAS(test::load_plugin,load_plugin)