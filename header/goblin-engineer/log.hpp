#pragma once

#include <string>
#include <iostream>
#include <chrono>
#include <mutex>

#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fmt/time.h>


namespace goblin_engineer {

    using std::chrono::system_clock;
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;
    using std::chrono::seconds;

    struct null_lock final {
        constexpr void lock() const noexcept {}
        constexpr bool try_lock() const noexcept { return true; }
        constexpr void unlock() const noexcept {}
    };

    struct null_log final {
        template<typename MSGBuilder>
        constexpr void trace(MSGBuilder &&) const noexcept {}

        template<typename MSGBuilder>
        constexpr void info(MSGBuilder &&) const noexcept {}

        template<typename MSGBuilder>
        constexpr void warn(MSGBuilder &&) const noexcept {}

        template<typename MSGBuilder>
        constexpr void error(MSGBuilder &&) const noexcept {}
    };


    template<typename Lock>
    class ostream_log final {
    public:
        ostream_log(const ostream_log &) = delete;

        ostream_log &operator=(const ostream_log &) = delete;

        ostream_log() noexcept: out_{&std::cout} {}

        explicit ostream_log(std::ostream &out) noexcept : out_{&out} {}

        template<typename MSGBuilder>
        void trace(MSGBuilder &&msg_builder) {
            log_message("TRACE", msg_builder());
        }

        template<typename MSGBuilder>
        void info(MSGBuilder &&msg_builder) {
            log_message(" INFO", msg_builder());
        }

        template<typename MSGBuilder>
        void warn(MSGBuilder &&msg_builder) {
            log_message(" WARN", msg_builder());
        }

        template<typename MSGBuilder>
        void error(MSGBuilder &&msg_builder) {
            log_message("ERROR", msg_builder());
        }

    private:
        void log_message(const char *tag, const std::string &msg) {
            std::unique_lock<Lock> lock{lock_};
            auto now = system_clock::now();
            auto ms = duration_cast<milliseconds>(now.time_since_epoch());
            time_t unix_time = duration_cast<seconds>(ms).count();

            (*out_)<< fmt::format(
                    "[{:%Y-%m-%d %H:%M:%S}.{:03d}] {}: {}",
                    make_localtime(unix_time),
                    static_cast< int >( ms.count() % 1000u ),
                    tag,
                    msg
            )<< std::endl;
        }

        Lock lock_;
        std::ostream *out_;
    };

    using ostream_log_type_null_lock = ostream_log<null_lock>;
    using ostream_log_type = ostream_log<std::mutex>;

}