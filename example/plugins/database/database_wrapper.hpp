#ifndef PLUGIN_WRAPPER_DATABASE_HPP
#define PLUGIN_WRAPPER_DATABASE_HPP

#include <iostream>
#include "goblin-engineer/plugin.hpp"
#include "database.hpp"

class database_wrapper final
        : public goblin_engineer::abstract_plugin,
          public database_t {
public:

    explicit database_wrapper(const std::string &);

    ~database_wrapper();

    goblin_engineer::metadata_t* metadata() const;

    void startup(const YAML::Node&);

    void shutdown();

    goblin_engineer::result call(const std::string&,goblin_engineer::virtual_args&& );

    void initialization(goblin_engineer::context_t *);

private:
    class impl;
    std::unique_ptr<impl> pimpl;

};

#endif //PLUGIN_DATABASE_HPP
