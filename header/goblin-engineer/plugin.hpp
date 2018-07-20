#pragma once

#include <string>
#include <goblin-engineer/abstract_plugin.hpp>

namespace goblin_engineer {


    enum class plugin_state : char {
        registered,  ///< the plugin is constructed but doesn't do anything
        initialized, ///< the plugin has initlaized any state required but is idle
        started,     ///< the plugin is actively running
        stopped      ///< the plugin is no longer running
    };
    /// contaner service and mini local env
    class plugin final {
    public:

        plugin() = default;

        plugin(plugin&&) = default;

        plugin&operator=(plugin&&) = default;

        plugin(abstract_plugin*);

        ~plugin() = default;

        void startup(const YAML::Node &options);

        void initialization(context_t *context);

        void shutdown();

        void  metadata(metadata_plugin*) const;

        void state(plugin_state);

        plugin_state state() const;

    private:
        plugin_state state_;

        std::unique_ptr<abstract_plugin> plugin_;

        inline auto self() -> abstract_plugin * {
            return plugin_.get();
        }

        inline auto self() const -> const abstract_plugin * {
            return plugin_.get();
        }
    };
}
