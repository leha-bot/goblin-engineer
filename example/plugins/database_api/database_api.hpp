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

class database_api final: public application::abstract_plugin{
public:
    explicit database_api();
    ~database_api();

    balance_output balance() const;

    application::metadata_t* metadata() const;

    void startup(const boost::program_options::variables_map&);

    void shutdown();

    void initialization(application::context_t *);

    application::result call(const std::string&,application::virtual_args&& );

private:
    class impl;
    application::utils::pimpl_ptr<impl>pimpl;
};

#endif //PLUGIN_DATABASE_API_HPP
