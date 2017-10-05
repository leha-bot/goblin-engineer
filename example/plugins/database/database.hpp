#ifndef PLUGIN_DATABASE_HPP
#define PLUGIN_DATABASE_HPP

#include <cstdint>
#include <unordered_map>
#include <iostream>
#include "handler.hpp"
#include "block.hpp"


class change_balance final : public handler {
public:
    explicit change_balance(database_t &db) : handler(db) {}
    ~change_balance()= default;
    void apply(const block &b) override;

    uint64_t id() const override;

};

class database_t {
private:

    class handler_storage final {
    public:
        handler_storage() = default;
        ~handler_storage()= default;
        template<typename Handler, typename ...Args>
        void add(database_t &db, Args &&... args) {
            handler *tmp = new Handler(db, std::forward<Args>(args)...);
            storage.emplace(tmp->id(), tmp);
        }

        bool transformation(const block &b);

    private:
        std::unordered_map<uint64_t, std::unique_ptr<handler>> storage;
    };

public:
    database_t();

    database_t(const database_t &) = delete;

    database_t &operator=(const database_t &)= delete;

    virtual ~database_t() = default;

    uint64_t balance() const;

    void balance(uint64_t balance_);

    void push_block(const block &b);

private:
    uint64_t balance_;
    handler_storage handlers;
};




#endif //PLUGIN_DATABASE_HPP
