#include <iostream>
#include <vector>
#include <unordered_map>
#include "database_api.hpp"
#include "application/context.hpp"

class database_api::impl final {
public:

    constexpr static const char *__name__ = "database_api";

    impl() {}

    ~impl() {}

    void context(application::context_t *__context__) {
        context_ = __context__;
    }

    void inject() {
    }

    template<typename F>
    void add_route(std::string name, F &f) {
        methods.emplace(name,f);
    }

private:
    std::unordered_map<std::string, application::method> methods;
    application::context_t *context_;
};

balance_output database_api::balance() const {
    std::cerr << "^_*_^" << std::endl;
    balance_output tmp{};
    //tmp.arg = db.balance();
    return tmp;
}

database_api::database_api() {
    std::cerr<<impl::__name__<<std::endl;
}

database_api::~database_api() {
    std::cerr<<"~"<<impl::__name__<<std::endl;
}

std::string database_api::plugin_name() const {
    std::cerr<<"plugin_name:"<<impl::__name__<<std::endl;
    return impl::__name__;
}

void database_api::plugin_startup(const boost::program_options::variables_map &) {
    std::cerr<<"plugin_startup :"<<impl::__name__<<std::endl;
}

void database_api::plugin_shutdown() {
    std::cerr<<"plugin_shutdown:"<<impl::__name__<<std::endl;
}

void database_api::plugin_initialization(application::context_t *) {
    std::cerr<<"plugin_initialization:"<<impl::__name__<<std::endl;
}

application::result database_api::execute(const std::string &, application::virtual_args &&) {
    return application::result();
}
