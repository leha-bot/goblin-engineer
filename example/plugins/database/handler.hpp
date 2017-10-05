#ifndef PLUGIN_HANDLER_HPP
#define PLUGIN_HANDLER_HPP

#include "block.hpp"

class database_t;

class handler {
public:
    explicit handler(database_t &db) : db(db) {}

    virtual ~handler()= default;

    virtual void apply(const block &) = 0;

    virtual uint64_t id() const = 0;

protected:
    database_t &db;
};
#endif //PLUGIN_HANDLER_HPP
