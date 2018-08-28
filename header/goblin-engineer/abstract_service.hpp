#pragma once
#include <cstdint>
#include <iostream>
#include <queue>
#include <unordered_map>

#include <goblin-engineer/message.hpp>
#include <goblin-engineer/service.hpp>

#include <actor-zeta/environment/abstract_group.hpp>
#include <actor-zeta/environment/group.hpp>

namespace goblin_engineer {

    using actor_zeta::environment::abstract_group;

    using actor_zeta::actor::abstract_actor;

    using actor_zeta::actor::actor;

    struct pipe {

        virtual ~pipe()                                                     = default;

        virtual bool send(message&&)                                        = 0;

        virtual std::string name() const                                    = 0;

    };

    struct abstract_service : public pipe {

        abstract_service();

        virtual ~abstract_service();

        static constexpr bool managed = false;

        static constexpr bool in_plugin = false;

        virtual void startup(context_t *)                                   = 0;

        virtual void shutdown()                                             = 0;

        virtual void metadata(metadata_service*) const                      = 0;

        virtual void join(service & )                                       = 0;

        pipe* to_pipe();

        service_state state_;
    };


    struct abstract_service_managed:
            public abstract_service {
            static constexpr bool managed = true;

        virtual ~abstract_service_managed();

        auto unpack() -> abstract_actor*;

        auto pack(actor_zeta::environment::group&&) -> void;

        void join(service & ) override;

        bool send(message&&) override;

        auto group() -> actor_zeta::environment::group&;

    protected:
        std::unique_ptr<abstract_actor> actor;
        actor_zeta::environment::group group_;

    };

    struct abstract_service_unmanaged:
            public abstract_service {

        virtual ~abstract_service_unmanaged();

        virtual bool send(message&&) override ;

        virtual void join(service &s) override ;

    protected:

        template <typename F>
        inline void add(const std::string& name, F&&f){
            method_table.emplace(name,std::forward<F>(f));
        }

        std::unordered_map<std::string,method> method_table;
        std::unordered_map<std::string,service> services;
    };




}

