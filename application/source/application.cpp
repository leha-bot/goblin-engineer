#include <unordered_map>
#include <vector>
#include <iostream>

#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/filesystem.hpp>
#include <boost/asio.hpp>

#include "../header/application/application.hpp"
#include "../header/application/plugin.hpp"
#include "../header/application/abstract_plugin.hpp"
#include "../header/application/metadata.hpp"
namespace application {

    inline std::string name(abstract_plugin* ptr){
        std::string tmp;
        tmp = ptr->metadata()->name;
        return tmp;
    }

    class application::impl final {
    public:
        impl(int argc, char **argv):io_serv(std::make_shared<boost::asio::io_service>()){
            boost::program_options::store(boost::program_options::parse_command_line(argc, argv, app_options_), args_);
            boost::program_options::notify(args_);
        }

        ~impl() {}

        void add_plugin(abstract_plugin *plugin) {
            auto size = storage_plugin.size();
            storage_plugin.emplace_back(plugin);
            mapper.emplace(name(plugin), size);
            state_plugin.emplace_back(size);
        }

        plugin&get_plugin(std::size_t index) {
            return storage_plugin.at(index);
        }

        plugin&get_plugin(const std::string __name__) {
            auto index = mapper.find(__name__);
            return storage_plugin.at(index->second);
        }

        state_t state(std::size_t index) const {
            return storage_plugin.at(index).state();
        }

        result invoke(const std::string &name_space, const std::string method, virtual_args&& args) {
            return get_plugin(name_space).call(method, std::forward<virtual_args>(args));
        }

        std::vector<std::size_t> &current_state() {
            return state_plugin;
        }

        boost::asio::io_service* loop(){
            return io_serv.get();
        }

        boost::program_options::variables_map args_;

    private:
        boost::program_options::options_description app_options_;
        boost::program_options::options_description cfg_options_;

        boost::filesystem::path data_dir;

        std::shared_ptr< boost::asio::io_service >    io_serv;
        /// plugin
        std::vector<plugin> storage_plugin;
        std::unordered_map<std::string, std::size_t> mapper;
        std::vector<std::size_t> state_plugin;
        /// plugin

    };

    void application::shutdown() {

        for (const auto &i:pimpl->current_state()) {
            if (pimpl->state(i) == state_t::started) {
                pimpl->get_plugin(i).shutdown();
            }
        }

        pimpl->loop()->stop();

    }

    void application::startup() {

        for (const auto &i:pimpl->current_state()) {
            if (pimpl->state(i) == state_t::initialized) {
                pimpl->get_plugin(i).startup(pimpl->args_);
            }
        }

        std::shared_ptr<boost::asio::signal_set> sigint_set(new boost::asio::signal_set(*pimpl->loop(), SIGINT));
        sigint_set->async_wait(
                [sigint_set,this](const boost::system::error_code& err, int num) {
                    shutdown();
                    sigint_set->cancel();
                }
        );

        std::shared_ptr<boost::asio::signal_set> sigterm_set(new boost::asio::signal_set(*pimpl->loop(), SIGTERM));
        sigterm_set->async_wait(
                [sigterm_set,this](const boost::system::error_code& err, int num) {
                    shutdown();
                    sigterm_set->cancel();
                }
        );

        pimpl->loop()->run();

        shutdown();
    }

    void application::initialize() {

        for (const auto &i:pimpl->current_state()) {
            if (pimpl->state(i) == state_t::registered) {
                pimpl->get_plugin(i).initialization(context());
            }
        }

    }

    application::application(int argc, char **argv) : pimpl(std::make_unique<impl>(argc,argv)) {}

    void application::add_plugin(abstract_plugin *plugin) {
        pimpl->add_plugin(plugin);
    }

    application::~application() {
        std::cerr << "~application" << std::endl;
    }

    result application::call(const std::string &name_space, const std::string &method, virtual_args &&args) {
        return pimpl->invoke(name_space, method,std::forward<virtual_args >( args));
    }

    context_t *application::context() {
        return this;
    }
}