#pragma once

namespace goblin_engineer {

    struct context_t;

    class service;

    class plugin;

    struct abstract_plugin;

    struct abstract_service;

    struct abstract_service_unmanaged;

    struct abstract_service_managed;

    struct metadata_plugin;

    struct metadata_service;

    enum class service_state : unsigned char {
        initialized,         ///< the service has initlaized any state required but is idle
        started,             ///< the service is actively running
        stopped              ///< the service is no longer running
    };


    enum class plugin_state : unsigned char {
        registered,  ///< the plugin is constructed but doesn't do anything
        initialized, ///< the plugin has initlaized any state required but is idle
        started,     ///< the plugin is actively running
        stopped      ///< the plugin is no longer running
    };

}
