#ifndef PLUGIN_WRAPPER_DATABASE_HPP
#define PLUGIN_WRAPPER_DATABASE_HPP

#include <iostream>
#include "application/plugin.hpp"
#include "application/pimpl.hpp"
#include "application/rpc.hpp"
#include "database.hpp"

class database_wrapper final
        : public application::plugin<database_wrapper>,
          public database_t {
public:

    explicit database_wrapper(const std::string &);

    ~database_wrapper();

    std::string plugin_name() const;

    void plugin_startup(const boost::program_options::variables_map&);

    void plugin_shutdown();

    void plugin_initialization(application::context_t *);

private:
    class impl;
    application::utils::pimpl_ptr<impl> pimpl;

};

#endif //PLUGIN_DATABASE_HPP
