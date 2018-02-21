#include "database_wrapper.hpp"
#include "database.hpp"
#include <memory>
#include "goblin-engineer/application.hpp"
#include "goblin-engineer/context.hpp"
#include "goblin-engineer/metadata.hpp"

class database_wrapper::impl final {
public:

    constexpr static const char *__name__ = "database";

    impl():tmp(new goblin_engineer::metadata_t) {
        tmp->name=__name__;
    }

    ~impl() = default;

    void context(goblin_engineer::context_t *__context__) {
        context_.reset(__context__);
    }

    void inject() {
    }

    template<std::size_t Size, typename F>
    void add_route(const char(&name)[Size], F &&f) {
        methods.emplace(std::string{name,Size-1}, f);
    }

    goblin_engineer::result execute(const std::string&method,goblin_engineer::virtual_args &&args) {
        auto it = methods.find(method);
        return it->second(std::forward<goblin_engineer::virtual_args>(args));
    }

    goblin_engineer::context context_;
    goblin_engineer::metadata_t* tmp;
private:

    std::unordered_map<std::string, goblin_engineer::method> methods;

};

void database_wrapper::startup(const YAML::Node&) {
    std::cerr << "startup database_wrapper" << std::endl;
}

void database_wrapper::shutdown() {
    std::cerr << "shutdown database_wrapper" << std::endl;

}

void database_wrapper::initialization(goblin_engineer::context_t *context) {
    std::cerr << "initialization database_wrapper" << std::endl;
    if (context != nullptr) {
        pimpl->context(context);
        pimpl->inject();
    }
}

goblin_engineer::metadata_t* database_wrapper::metadata() const {
    return pimpl->tmp;
}

database_wrapper::database_wrapper(const std::string &path) : pimpl(new impl()) {
    std::cerr<<"database_wrapper"<<std::endl;
    std::cerr << path << std::endl;
    pimpl->add_route(
            "push_back",
            [&, this](goblin_engineer::virtual_args&& args) -> goblin_engineer::result {
                auto arg_1 = block(1, 1);
                push_block(arg_1);
            }
    );
}

database_wrapper::~database_wrapper() {
    std::cerr<<"~database_wrapper"<<std::endl;
}

goblin_engineer::result database_wrapper::call(const std::string&method,goblin_engineer::virtual_args &&args) {
return pimpl->execute(method,std::forward<goblin_engineer::virtual_args>(args));
}




