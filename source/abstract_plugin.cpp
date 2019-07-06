#include <utility>

#include <goblin-engineer/abstract_plugin.hpp>

namespace goblin_engineer {

    struct library_holding_deleter final {
        std::unique_ptr<boost::dll::shared_library> lib_;

        void operator()(abstract_plugin* p) const {
            delete p;
        }
    };

    auto get_plugin(boost::filesystem::path path, const char *func_name) -> abstract_plugin* {
        typedef abstract_plugin*(func_t)();
        auto lib = boost::dll::shared_library(
                path,
                boost::dll::load_mode::append_decorations   // will be ignored for executable
        );
        library_holding_deleter deleter;
        deleter.lib_ = std::move(lib);
        auto p = lib.get_alias<abstract_plugin*()>(func_name);
        auto ddd = std::unique_ptr<abstract_plugin,>(new abstract_plugin(p,library_holding_deleter));
        return  ddd;
    }

    auto load_plugin(boost::filesystem::path path) -> abstract_plugin * {
        return get_plugin(std::move(path),"load_plugin");
    }
}