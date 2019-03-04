#include <iostream>
#include "goblin-engineer/plugin.hpp"
#include "goblin-engineer/abstract_plugin.hpp"

namespace goblin_engineer {

    inline std::string name(abstract_plugin* ptr){
        std::string tmp;
        std::unique_ptr<meta_data_plugin> metadata(new meta_data_plugin);
        ptr->meta_data(metadata.get());
        tmp = metadata->name;
        return tmp;
    }

    void plugin::state(plugin_state state_) {
        this->state_ = state_;
    }

    plugin_state plugin::state() const {
        return state_;
    }

    plugin::plugin(abstract_plugin *ptr) :
        state_(plugin_state::registered),
        plugin_(ptr){
    }

    void plugin::startup(context_t*context) {
        std::cerr << "startup plugin: " << name(self()) << std::endl;
        if (state() == plugin_state::initialized) {
            state(plugin_state::started);
            return self()->startup(context);
        } else {
            std::cerr << "error startup  plugin: " << name(self()) << std::endl;
        }
    }

    void plugin::initialization() {
        std::cerr << "initialization plugin: " << name(self()) << std::endl;
        if (state() == plugin_state::registered) {
            state(plugin_state::initialized);
            return self()->initialization();
        } else {
            std::cerr << "error initialization plugin: " << name(self()) << std::endl;
        }
    }

    void plugin::shutdown() {
        std::cerr << "shutdown plugin:" << name(self()) << std::endl;
        if (state() == plugin_state::started) {
            state(plugin_state::stopped);
            return self()->shutdown();
        } else {
            std::cerr << "error shutdown plugin:" << name(self()) << std::endl;
        }

    }

    void plugin::metadata(meta_data_plugin* metadata) const {
        self()->meta_data(metadata);
    }

    auto plugin::self() -> abstract_plugin * {
        return plugin_.get();
    }

    auto plugin::self() const -> const abstract_plugin * {
        return plugin_.get();
    }
}