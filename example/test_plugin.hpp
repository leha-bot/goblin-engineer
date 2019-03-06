#pragma once

#include <goblin-engineer/abstract_plugin.hpp>

#ifdef __cplusplus
extern "C" {
#endif

class BOOST_SYMBOL_VISIBLE test_plugin final : public goblin_engineer::abstract_plugin {

    void initialization(goblin_engineer::dynamic_config &,
                        actor_zeta::environment::abstract_environment *
    ) override;

    void startup(goblin_engineer::context_t *) override;

    void meta_data(goblin_engineer::meta_data_plugin*) const override;

    ~test_plugin() override = default;

};

#ifdef __cplusplus
}
#endif
