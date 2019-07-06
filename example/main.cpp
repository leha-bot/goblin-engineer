#include <iostream>
#include <boost/filesystem.hpp>
#include <goblin-engineer/abstract_plugin.hpp>


int main() {

    auto* plugin = goblin_engineer::load_plugin("libProgPlugin.dylib");

    ///plugin->meta_data()

    return 0;
}