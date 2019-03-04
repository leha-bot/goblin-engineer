#include <iostream>
#include <goblin-engineer/abstract_plugin.hpp>


int main() {

    auto plugin = goblin_engineer::get_plugin(
            boost::dll::program_location(),
            "create_refc_plugin"
    );

    return 0;
}