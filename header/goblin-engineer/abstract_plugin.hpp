#pragma once
#include <cstdint>

#include <boost/dll.hpp>


#include <goblin-engineer/context.hpp>
#include <actor-zeta/ref_counted.hpp>

namespace goblin_engineer {

    struct BOOST_SYMBOL_VISIBLE meta_data_plugin final {
        std::string name;
        std::vector<meta_data_plugin> dependency;
        std::size_t major;
        std::size_t minor;
        std::size_t patch_level;
    };

    ///class factory

    struct BOOST_SYMBOL_VISIBLE abstract_plugin {

        virtual void initialization(
                goblin_engineer::dynamic_config &,
                actor_zeta::environment::abstract_environment *
        ) = 0;

        virtual void startup(context_t *) = 0;

        virtual void meta_data(meta_data_plugin *) const = 0;

        virtual ~abstract_plugin() = default;
    };


    auto get_plugin(boost::filesystem::path path, const char *func_name) -> abstract_plugin*;

    auto load_plugin(boost::filesystem::path) -> abstract_plugin*;

}

