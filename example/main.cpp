#include "application/application.hpp"
#include "plugins/database/database_wrapper.hpp"
#include "plugins/database_api/database_api.hpp"

int main(int argc, char **argv) {

    application::application_ptr app(new application::application(argc,argv));
    application::add_plugin<database_wrapper>(app, std::string("/opt/boost/"));
    application::add_plugin<database_api>(app);
    app->initialize();
    app->startup();
    return 0;

}