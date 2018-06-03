#pragma once

#include <boost/any.hpp>
#include <functional>
#include <vector>

namespace goblin_engineer {

    struct context_t;

    struct abstract_plugin;

    struct metadata_t;

    using result = void;

    using virtual_args = std::vector<boost::any>;

    using method = std::function<result(virtual_args&&)>;
}
#endif //PLUGIN_FORWARD_HPP
