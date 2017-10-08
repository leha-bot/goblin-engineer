#ifndef PLUGIN_FORWARD_HPP
#define PLUGIN_FORWARD_HPP

#include <boost/any.hpp>

namespace application {
    class context_t;

    class abstract_plugin;

    using result = boost::any;

    using virtual_args = std::vector<boost::any>;

    using method = std::function<result(virtual_args&&)>;
    
}
#endif //PLUGIN_FORWARD_HPP
