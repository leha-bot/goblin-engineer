#ifndef METADATA_HPP
#define METADATA_HPP
#include <string>
#include <vector>

namespace goblin_engineer {

    struct metadata_t {
        std::string name;
        std::vector<metadata_t> dependency;
        std::size_t major;
        std::size_t minor;
        std::size_t patch_level;
    };

}
#endif //PROJECT_METADATA_HPP
