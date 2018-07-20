#pragma once

#include <goblin-engineer/forward.hpp>

namespace goblin_engineer {

    using virtual_result = std::vector<boost::any>;

    using virtual_args = std::vector<boost::any>;

    struct msg final {
        std::string    method;
        virtual_args   args;
        virtual_result result;
    };

    using method = std::function<void(msg&&)>;

}