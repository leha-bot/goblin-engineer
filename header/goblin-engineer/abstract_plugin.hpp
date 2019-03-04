#pragma once
#include <cstdint>

#include <boost/dll.hpp>
#include <boost/filesystem.hpp>

#include <goblin-engineer/context.hpp>
#include <actor-zeta/ref_counted.hpp>

namespace goblin_engineer {
    /// container service

    struct meta_data_plugin;

    struct BOOST_SYMBOL_VISIBLE abstract_plugin : public actor_zeta::ref_counted  {

        virtual void initialization(void)               = 0;

        virtual void startup(context_t *)               = 0;

        virtual void shutdown(void)                     = 0;

        virtual void meta_data(meta_data_plugin*) const = 0;

        virtual ~abstract_plugin()                      = default;
    };


    auto get_plugin(boost::filesystem::path path, const char* func_name) -> actor_zeta::intrusive_ptr<abstract_plugin>;

    #define PLUGIN_API extern "C" BOOST_SYMBOL_EXPORT

    PLUGIN_API struct meta_data_plugin final {
        std::string name;
        std::vector<meta_data_plugin> dependency;
        std::size_t major;
        std::size_t minor;
        std::size_t patch_level;
    };

}

