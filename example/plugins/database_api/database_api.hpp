#ifndef PLUGIN_DATABASE_API_HPP
#define PLUGIN_DATABASE_API_HPP


#include <application/pimpl.hpp>
#include "application/plugin.hpp"

struct balance_output final {
    uint64_t arg;

    friend std::ostream &operator<<(std::ostream &os, const balance_output &args1) {
        os << "args: " << args1.arg;
        return os;
    }
};

class database_api final: public application::plugin<database_api>{
public:
    explicit database_api();
    ~database_api();

    balance_output balance() const;

    std::string plugin_name() const;

    void plugin_startup(const boost::program_options::variables_map&);

    void plugin_shutdown();

    void plugin_initialization(application::context_t *);

    application::result execute(const std::string&,application::virtual_args&& );

private:
    class impl;
    application::utils::pimpl_ptr<impl>pimpl;
};

#endif //PLUGIN_DATABASE_API_HPP
