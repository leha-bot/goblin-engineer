#pragma once

#include <vector>
#include <functional>
#include <boost/any.hpp>

namespace goblin_engineer {

    using virtual_result = std::vector<boost::any>;

    using virtual_args = std::vector<boost::any>;

    struct message final {
        message(
                const std::string &sender,
                const std::string &method,
                const virtual_args &args
        );
        ~message();

        std::string    sender;
        std::string    method;
        virtual_args   args;
        virtual_result result;
    };

    using method = std::function<void(message&&)>;

}