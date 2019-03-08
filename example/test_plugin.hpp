#pragma once

#include <goblin-engineer/abstract_plugin.hpp>
#include <actor-zeta/actor/abstract_actor.hpp>
#include <actor-zeta/actor/basic_actor.hpp>

class BOOST_SYMBOL_VISIBLE example_plugin_actor final : actor_zeta::actor::basic_async_actor {
public:
    example_plugin_actor(actor_zeta::environment::abstract_environment* env):basic_actor(env,"logger"){

    }

    ~example_plugin_actor() = default;
};

class BOOST_SYMBOL_VISIBLE example_plugin_service final : public goblin_engineer::abstract_plugin {
public:
    example_plugin_service() = default;

    ~example_plugin_service() = default;

    void initialization(
            goblin_engineer::dynamic_config &,
            actor_zeta::environment::abstract_environment *
    ) override;

    void startup(goblin_engineer::context_t *) override;

    void meta_data(goblin_engineer::meta_data_plugin*) const override;

private:
    std::unique_ptr<example_plugin_actor> prototype;

};
