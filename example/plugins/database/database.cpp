#include "database.hpp"

database_t::database_t() {
    handlers.add<change_balance>(*this);
}

uint64_t database_t::balance() const {
    return balance_;
}

void database_t::balance(uint64_t balance_) {
    this->balance_ = balance_;
}

void database_t::push_block(const block &b) {
    handlers.transformation(b);
}

bool database_t::handler_storage::transformation(const block &b) {
    auto it = storage.find(b.actions);
    if (it != storage.end()) {
        it->second->apply(b);
        return true;
    }
    return false;
}

void change_balance::apply(const block &b) {
    std::cerr << "(_*_)" << std::endl;
    //db.balance(b.args);
}

uint64_t change_balance::id() const {
    //code handler
    return 1;
}
