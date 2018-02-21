#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/filesystem.hpp>

#include <goblin-engineer/application.hpp>
#include "plugins/database/database_wrapper.hpp"
#include "plugins/database_api/database_api.hpp"

constexpr const  char* config_name_file = "config.yaml";

constexpr const  char* data_name_file = "data";

constexpr const  char* plugins_name_file = "plugins";

int main(int argc, char **argv) {

    boost::program_options::variables_map args_;
    boost::program_options::options_description app_options_;

    app_options_.add_options()
            ("data-dir,d", "data-dir")
            ("plugins,p", boost::program_options::value<std::vector<std::string>>()->multitoken(), "data-dir")
            ;

    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, app_options_), args_);
    boost::program_options::notify(args_);

    boost::filesystem::path data_dir;
    boost::filesystem::path config_path;
    boost::filesystem::path plugins_dir;


    if (args_.count("data-dir")) {

        data_dir = args_["data-dir"].as<std::string>();

        config_path = data_dir / config_name_file;

    } else {

        boost::filesystem::path data_dir = boost::filesystem::current_path();

        auto data_path = data_dir / data_name_file;

        auto data_dir_path = data_dir / data_name_file;

        if (boost::filesystem::exists(data_path)) {
            boost::filesystem::create_directories(data_dir_path);
        }

        if (boost::filesystem::exists(data_dir_path)) {
            boost::filesystem::create_directories(data_dir_path / plugins_name_file);
            plugins_dir = data_dir_path / plugins_name_file;
        }

        config_path = data_path / config_name_file;

        std::ofstream outfile(config_path.string());

        outfile.close();
    }

    goblin_engineer::configuration config;

    if (args_.count("plugins") ) {
        auto& plugins  = args_["plugins"].as<std::vector<std::string>>();
        for(auto&&i:plugins){
            config.plugins.emplace(std::move(i));
        }
    }

    config.plugins.emplace("database_api");
    config.plugins.emplace("database");
    config.data_dir    = data_dir.string();
    config.config_path = config_path.string();
    config.plugins_dir = plugins_dir.string();
    config.signal.emplace(SIGINT);
    config.signal.emplace(SIGTERM);


    goblin_engineer::application app;

    app.load_config(std::move(config));

    //TODO Boots.DLL
    goblin_engineer::add_plugin<database_wrapper>(app, std::string("/opt/boost/"));
    goblin_engineer::add_plugin<database_api>(app);

    app.initialize();

    app.startup();

    return 0;
}