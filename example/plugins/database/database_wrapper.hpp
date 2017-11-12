#ifndef PLUGIN_WRAPPER_DATABASE_HPP
#define PLUGIN_WRAPPER_DATABASE_HPP

#include <iostream>
#include "application/plugin.hpp"
#include "application/pimpl.hpp"
#include "database.hpp"

class database_wrapper final
        : public application::abstract_plugin,
          public database_t {
public:

    explicit database_wrapper(const std::string &);

    ~database_wrapper();

    application::metadata_t* metadata() const;

    void startup(const boost::program_options::variables_map&);

    void shutdown();

    application::result call(const std::string&,application::virtual_args&& );

    void initialization(application::context_t *);

private:
    class impl;
    application::utils::pimpl_ptr<impl> pimpl;

};

#endif //PLUGIN_DATABASE_HPP
