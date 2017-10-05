#include "../header/application/abstract_plugin.hpp"

namespace application {


    void abstract_plugin::state(state_t state_) {
        this->state_ = state_;
    }

    state_t abstract_plugin::state() const {
        return state_;
    }

    abstract_plugin::abstract_plugin() : state_(state_t::registered) {}
}