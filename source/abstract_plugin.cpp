#include <utility>

#include <goblin-engineer/abstract_plugin.hpp>

namespace goblin_engineer {

    auto get_plugin(boost::filesystem::path path, const char *func_name) -> abstract_plugin* {
        typedef abstract_plugin*(func_t)();
        std::function<func_t> creator = boost::dll::import_alias<func_t>(
                path,
                func_name,
                boost::dll::load_mode::append_decorations   // will be ignored for executable
        );

        return creator();
    }

    auto load_plugin(boost::filesystem::path path) -> abstract_plugin * {
        return get_plugin(std::move(path),"load_plugin");
    }
}