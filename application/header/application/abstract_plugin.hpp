#ifndef ABSTRACT_PLUGIN_HPP
#define ABSTRACT_PLUGIN_HPP

#include <cstdint>

#include <boost/program_options/variables_map.hpp>

#include "forward.hpp"

namespace application {

    struct abstract_plugin {

        virtual void startup(const boost::program_options::variables_map &) = 0;

        virtual void shutdown()                                             = 0;

        virtual void initialization(context_t *)                            = 0;

        virtual metadata_t* metadata() const                                = 0;

        virtual result call(const std::string &, virtual_args &&)           = 0;

        virtual ~abstract_plugin() = default;
    };

}
#endif
