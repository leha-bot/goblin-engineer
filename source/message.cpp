#include <goblin-engineer/message.hpp>

namespace goblin_engineer {

    message::message(const std::string &sender, const std::string &method, const std::vector<boost::any> &args) :sender(sender), method(method), args(args) {}

    message::~message()  = default;
}
