#ifndef PLUGIN_RPC_HPP
#define PLUGIN_RPC_HPP

#include <unordered_map>
#include <vector>
#include <string>

#include <boost/any.hpp>

///TODO: BIGPROBLEM
namespace application {
    using result = boost::any;

    using virtual_args = std::vector<boost::any>;

    using method = std::function<result(virtual_args)>;

    class route_t final {
    public:
        explicit route_t(const std::string &name_);

        const std::string &name() const;

        template<typename F>
        void add_route(std::string name, F &&f) {
            methods.emplace(name, f);
        }

        result invoke(std::string method, virtual_args args);

    private:
        std::string name_;
        std::unordered_map<std::string, method> methods;
    };
}
#endif //PLUGIN_RPC_HPP
