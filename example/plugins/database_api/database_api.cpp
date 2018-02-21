#include <iostream>
#include <vector>
#include <unordered_map>
#include "database_api.hpp"
#include "goblin-engineer/context.hpp"
#include "goblin-engineer/metadata.hpp"

class database_api::impl final {
public:

    impl():tmp(new goblin_engineer::metadata_t) {
        tmp->name = "database_api";
        tmp->major = 0;
        tmp->minor = 0;
        tmp->patch_level = 0;
    }

    ~impl() {}

    void context(goblin_engineer::context_t *__context__) {
        context_.reset(__context__);
    }

    void inject() {
    }

    template<typename F>
    void add_route(std::string name, F &f) {
        methods.emplace(name,f);
    }
    goblin_engineer::metadata_t* tmp;
private:
    std::unordered_map<std::string, goblin_engineer::method> methods;
    goblin_engineer::context context_;
};

balance_output database_api::balance() const {
    std::cerr << "^_*_^" << std::endl;
    balance_output tmp{};
    //tmp.arg = db.balance();
    return tmp;
}

database_api::database_api():pimpl(new impl) {
    std::cerr<<pimpl->tmp->name<<std::endl;
}

database_api::~database_api() {
    std::cerr<<"~"<<pimpl->tmp->name<<std::endl;
}

goblin_engineer::metadata_t* database_api::metadata() const {
    std::cerr<<"plugin_name:"<<pimpl->tmp->name<<std::endl;
    return pimpl->tmp;
}

void database_api::startup(const YAML::Node &) {
    std::cerr<<"plugin_startup :"<<pimpl->tmp->name<<std::endl;
}

void database_api::shutdown() {
    std::cerr<<"plugin_shutdown:"<<pimpl->tmp->name<<std::endl;
}

void database_api::initialization(goblin_engineer::context_t *ptr) {
    std::cerr<<"plugin_initialization:"<<pimpl->tmp->name<<std::endl;
    pimpl->context(ptr);
}

goblin_engineer::result database_api::call(const std::string &, goblin_engineer::virtual_args &&) {
    return goblin_engineer::result();
}
