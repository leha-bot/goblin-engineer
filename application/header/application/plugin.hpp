#ifndef PLUGIN_PLUGIN_H
#define PLUGIN_PLUGIN_H

#include <string>
#include "abstract_plugin.hpp"
namespace application {

    template<typename PLUGIN>
    struct allocator final {

    };

    template<typename PLUGIN, typename Allocator = allocator<PLUGIN>>
    class plugin : public abstract_plugin {
    public:

        void startup(const boost::program_options::variables_map &options) override final {
            std::cerr << "startup plugin: " << name() << std::endl;
            if (state() == state_t::initialized) {
                state(state_t::started);
                return self()->plugin_startup(options);
            } else {
                std::cerr << "error startup  plugin: " << name() << std::endl;
            }
        }

        void initialization(context_t *context) override final {
            std::cerr << "initialization plugin: " << name() << std::endl;
            if (state() == state_t::registered) {
                state(state_t::initialized);
                return self()->plugin_initialization(context);
            } else {
                std::cerr << "error initialization plugin: " << name() << std::endl;
            }
        }

        void shutdown() override final {
            std::cerr << "shutdown plugin:" << name() << std::endl;
            if (state() == state_t::started) {
                state(state_t::stopped);
                return self()->plugin_shutdown();
            } else {
                std::cerr << "error shutdown plugin:" << name() << std::endl;
            }

        }

        std::string name() const override final {
            return self()->plugin_name();
        }

    protected:
        plugin() : abstract_plugin() {}

        virtual ~plugin() = default;

    private:
        inline auto self() -> PLUGIN * {
            return static_cast<PLUGIN *>(this);
        }

        inline auto self() const -> const PLUGIN * {
            return static_cast<const PLUGIN *>(this);
        }
    };
}
#endif //PLUGIN_PLUGIN_H
