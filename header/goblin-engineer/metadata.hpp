#pragma once
#include <string>
#include <vector>

namespace goblin_engineer {

    struct metadata_plugin {
        std::string name;
        std::vector<metadata_plugin> dependency;
        std::size_t major;
        std::size_t minor;
        std::size_t patch_level;
    };
}
