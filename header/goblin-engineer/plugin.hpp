#pragma once

#include <goblin-engineer/abstract_plugin.hpp>

namespace goblin_engineer {

    /// contaner service and mini local env
    class plugin final {
    public:

        plugin() = default;

        plugin(plugin&&) = default;

        plugin&operator=(plugin&&) = default;

        plugin(abstract_plugin*);

        ~plugin() = default;

        void startup(context_t *);

        void initialization();

        void shutdown();

        void  metadata(meta_data_plugin*) const;

        void state(plugin_state);

        plugin_state state() const;

    private:
        plugin_state state_;

        std::unique_ptr<abstract_plugin> plugin_;

        auto self() -> abstract_plugin *;

        auto self() const -> const abstract_plugin *;
    };
}
