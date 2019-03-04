#pragma once


#include <goblin-engineer/abstract_plugin.hpp>

PLUGIN_API class  test_plugin final : public goblin_engineer::abstract_plugin {
    void initialization(void);

    void startup(goblin_engineer::context_t *);

    void shutdown(void);

    void metadata(goblin_engineer::metadata_plugin*) const;

    ~test_plugin()= default;
};
