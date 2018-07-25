#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace goblin_engineer {

    struct app_config final {
        std::string name;
        std::string init_script;
        std::unordered_map<std::string, std::string> ws;
        std::unordered_map<std::string, std::string> http;
    };

    struct plugin_config final {

    };


    struct service_config final {

    };

    struct config final {
        std::unordered_set<std::string>             scripts;
        std::unordered_set<std::string>             plugins;
        std::unordered_map<std::string, app_config> apps;
    };


    struct configuration final {
        std::string                     config_path;
        std::string                     plugins_dir;
        std::string                     data_dir;
        std::unordered_set<std::string> plugins;
        std::unordered_set<std::size_t> signal;

    };
}