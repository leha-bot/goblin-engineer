#ifndef METADATA_HPP
#define METADATA_HPP
#include <string>
#include <vector>

namespace application {

    struct metadata_t {
        std::string name;
        std::vector<std::string> dependency;
        std::size_t major;
        std::size_t minor;
        std::size_t patchlevel;
    };

}
#endif //PROJECT_METADATA_HPP
