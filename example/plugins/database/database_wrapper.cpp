#include "database_wrapper.hpp"
#include "database.hpp"
#include <memory>
#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <application/application.hpp>
#include "application/context.hpp"

class database_wrapper::impl final {
public:

    constexpr static const char *__name__ = "database";

    impl() {}

    ~impl() = default;

    void context(application::context_t *__context__) {
        context_.reset(__context__);
    }

    void inject() {
    }

    template<std::size_t Size, typename F>
    void add_route(const char(&name)[Size], F &&f) {
        methods.emplace(std::string{name,Size-1}, f);
    }

    application::result execute(const std::string&method,application::virtual_args &&args) {
        auto it = methods.find(method);
        return it->second(std::forward<application::virtual_args>(args));
    }

    boost::intrusive_ptr<application::context_t> context_;
private:

    std::unordered_map<std::string, application::method> methods;

};

void database_wrapper::plugin_startup(const boost::program_options::variables_map&) {
    std::cerr << "startup database_wrapper" << std::endl;
}

void database_wrapper::plugin_shutdown() {
    std::cerr << "shutdown database_wrapper" << std::endl;
    boost::sp_adl_block::intrusive_ptr_release(pimpl->context_.get());

}

void database_wrapper::plugin_initialization(application::context_t *context) {
    std::cerr << "initialization database_wrapper" << std::endl;
    if (context != nullptr) {
        pimpl->context(context);
        pimpl->inject();
    }
}

std::string database_wrapper::plugin_name() const {
    return impl::__name__;
}

database_wrapper::database_wrapper(const std::string &path) : pimpl(std::make_unique<impl>()) {
    std::cerr<<"database_wrapper"<<std::endl;
    std::cerr << path << std::endl;
    pimpl->add_route(
            "push_back",
            [&, this](application::virtual_args&& args) -> application::result {
                auto arg_1 = block(1, 1);
                push_block(arg_1);
            }
    );
}

database_wrapper::~database_wrapper() {
    std::cerr<<"~database_wrapper"<<std::endl;
}

application::result database_wrapper::execute(const std::string&method,application::virtual_args &&args) {
return pimpl->execute(method,std::forward<application::virtual_args>(args));
}




