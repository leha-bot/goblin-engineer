#include <goblin-engineer/abstract_plugin.hpp>

namespace goblin_engineer {

    auto get_plugin(boost::filesystem::path path, const char *func_name) -> actor_zeta::intrusive_ptr<abstract_plugin> {
        typedef abstract_plugin*(func_t)();
        std::function<func_t> creator = boost::dll::import_alias<func_t>(
                path,
                func_name,
                boost::dll::load_mode::append_decorations   // will be ignored for executable
        );

        abstract_plugin* plugin = creator();

        return actor_zeta::intrusive_ptr<abstract_plugin>(plugin);

    }
}