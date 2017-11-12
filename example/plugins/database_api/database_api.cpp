#include <iostream>
#include <vector>
#include <unordered_map>
#include "database_api.hpp"
#include "application/context.hpp"
#include "application/metadata.hpp"

class database_api::impl final {
public:



    impl():tmp(new application::metadata_t) {
        tmp->name = "database_api";
        tmp->major = 0;
        tmp->minor = 0;
        tmp->patchlevel = 0;
    }

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
    application::metadata_t* tmp;
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
    std::cerr<<pimpl->tmp->name<<std::endl;
}

database_api::~database_api() {
    std::cerr<<"~"<<pimpl->tmp->name<<std::endl;
}

application::metadata_t* database_api::metadata() const {
    std::cerr<<"plugin_name:"<<pimpl->tmp->name<<std::endl;
    return pimpl->tmp;
}

void database_api::startup(const boost::program_options::variables_map &) {
    std::cerr<<"plugin_startup :"<<pimpl->tmp->name<<std::endl;
}

void database_api::shutdown() {
    std::cerr<<"plugin_shutdown:"<<pimpl->tmp->name<<std::endl;
}

void database_api::initialization(application::context_t *) {
    std::cerr<<"plugin_initialization:"<<pimpl->tmp->name<<std::endl;
}

application::result database_api::call(const std::string &, application::virtual_args &&) {
    return application::result();
}
