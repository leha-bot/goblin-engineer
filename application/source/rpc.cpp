#include "../header/application/rpc.hpp"
namespace application {
    result route_t::invoke(const std::string method, virtual_args args) {
        auto m = methods.find(method);
        return m->second(args);
    }

    const std::string &route_t::name() const {
        return name_;
    }

    route_t::route_t(const std::string &name_) : name_(name_) {}
}