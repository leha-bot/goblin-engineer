#ifndef PLUGIN_CONTEXT_HPP
#define PLUGIN_CONTEXT_HPP

#include "forward.hpp"

#include <boost/smart_ptr/intrusive_ref_counter.hpp>

namespace application {

    struct context_t : public boost::intrusive_ref_counter<context_t, boost::thread_safe_counter> {

        virtual result call(const std::string &name_space, const std::string &method, virtual_args &&args) = 0;

        virtual ~context_t() = default;

    };
}

#endif //PLUGIN_CONTEXT_HPP
