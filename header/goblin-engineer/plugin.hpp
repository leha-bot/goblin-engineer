#ifndef PLUGIN_PLUGIN_H
#define PLUGIN_PLUGIN_H

#include <string>
#include "abstract_plugin.hpp"

namespace goblin_engineer {


    enum class state_t : uint8_t {
        registered,  ///< the plugin is constructed but doesn't do anything
        initialized, ///< the plugin has initlaized any state required but is idle
        started,     ///< the plugin is actively running
        stopped      ///< the plugin is no longer running
    };

    class plugin final {
    public:

        plugin() = default;

        plugin(plugin&&) = default;

        plugin&operator=(plugin&&) = default;

        plugin(abstract_plugin*);

        ~plugin() = default;

        result call(const std::string &method, virtual_args &&args);

        void startup(const YAML::Node &options);

        void initialization(context_t *context);

        void shutdown();

        metadata_t* metadata() const;

        void state(state_t);

        state_t state() const;

    private:
        state_t state_;

        std::unique_ptr<abstract_plugin> plugin_;

        inline auto self() -> abstract_plugin * {
            return plugin_.get();
        }

        inline auto self() const -> const abstract_plugin * {
            return plugin_.get();
        }
    };
}
#endif //PLUGIN_PLUGIN_H
