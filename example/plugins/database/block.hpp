#ifndef PLUGIN_BLOCK_HPP
#define PLUGIN_BLOCK_HPP
struct block final {
    block(uint64_t actions, uint64_t args) : actions(actions), args(args) {}

    uint64_t actions;
    uint64_t args;
};
#endif //PLUGIN_BLOCK_HPP
