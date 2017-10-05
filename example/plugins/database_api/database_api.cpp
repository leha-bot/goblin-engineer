#include <iostream>
#include "database_api.hpp"
#include "application/context.hpp"

class database_api::impl final {
public:

    constexpr static const char *__name__ = "database_api";

    impl() : route(__name__) {}

    ~impl() {}

    void context(application::context_t *__context__) {
        context_ = __context__;
    }

    void inject() {
        context_->add_route(route);
    }

    template<typename F>
    void add_route(std::string name, F &f) {
        route.add_route(name, f);
    }

    std::vector<int> ff;
private:
    application::route_t route;
    application::context_t *context_;
};

balance_output database_api::balance() const {
    std::cerr << "^_*_^" << std::endl;
    balance_output tmp{};
    //tmp.arg = db.balance();
    return tmp;
}

database_api::database_api() {
    std::cerr<<"database_api"<<std::endl;
}

database_api::~database_api() {
    std::cerr<<"~database_api"<<std::endl;
}

std::string database_api::plugin_name() const {
    std::cerr<<"plugin_name"<<std::endl;
    return impl::__name__;
}

void database_api::plugin_startup(const boost::program_options::variables_map &) {
    std::cerr<<"plugin_startup"<<std::endl;
}

void database_api::plugin_shutdown() {
    std::cerr<<"plugin_shutdown"<<std::endl;
}

void database_api::plugin_initialization(application::context_t *) {
    std::cerr<<"plugin_initialization"<<std::endl;
}
