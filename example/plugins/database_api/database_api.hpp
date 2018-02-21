#ifndef PLUGIN_DATABASE_API_HPP
#define PLUGIN_DATABASE_API_HPP


#include <yaml-cpp/yaml.h>
#include "goblin-engineer/plugin.hpp"

struct balance_output final {
    uint64_t arg;

    friend std::ostream &operator<<(std::ostream &os, const balance_output &args1) {
        os << "args: " << args1.arg;
        return os;
    }
};

class database_api final: public goblin_engineer::abstract_plugin {
public:
    explicit database_api();
    ~database_api();

    balance_output balance() const;

    goblin_engineer::metadata_t* metadata() const;

    void startup(const YAML::Node&);

    void shutdown();

    void initialization(goblin_engineer::context_t *);

    goblin_engineer::result call(const std::string&,goblin_engineer::virtual_args&& );

private:
    class impl;
    std::unique_ptr<impl>pimpl;
};

#endif //PLUGIN_DATABASE_API_HPP
