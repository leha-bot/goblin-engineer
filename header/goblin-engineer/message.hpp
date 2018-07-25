#pragma once

#include <goblin-engineer/forward.hpp>

namespace goblin_engineer {

    using virtual_result = std::vector<boost::any>;

    using virtual_args = std::vector<boost::any>;

    struct msg final {
        msg(const std::string &method, const std::vector<boost::any> &args) : method(method), args(args) {}

        std::string    method;
        virtual_args   args;
        virtual_result result;
    };

    using method = std::function<void(msg&&)>;

}