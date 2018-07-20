#pragma once
#include <cstdint>
#include <iostream>
#include <queue>
#include <unordered_map>

#include <yaml-cpp/yaml.h>

#include <goblin-engineer/message.hpp>
#include <goblin-engineer/service.hpp>

#include <actor-zeta/environment/abstract_group.hpp>
#include <actor-zeta/environment/group.hpp>



namespace goblin_engineer {

    using actor_zeta::environment::abstract_group;

    using actor_zeta::actor::abstract_actor;
    using actor_zeta::actor::actor;

    struct abstract_service {

        virtual ~abstract_service()                                         = default;

        static constexpr bool managed = false;

        virtual void startup(const YAML::Node &)                            = 0;

        virtual void shutdown()                                             = 0;

        virtual void initialization(context_t *)                            = 0;

        virtual void metadata(metadata_service*) const                      = 0;

        virtual void join(service & )                                       = 0;

        virtual bool send(msg&&)                                            = 0;

        virtual void input(service &s)                                      = 0;

        virtual void output(service &s)                                     = 0;

        virtual auto input() const -> const std::string&                    = 0;

        virtual auto output() const -> const std::string&                   = 0;

    };


    struct abstract_service_managed:
            public abstract_service {
            static constexpr bool managed = true;

        virtual ~abstract_service_managed()                                 = default;

        auto unpack() -> abstract_actor*;

        auto pack(actor_zeta::environment::group&&) -> void;

        void join(service & s);

        bool send(msg&&);

        auto group() -> actor_zeta::environment::group&;

    protected:
        std::unique_ptr<abstract_actor> actor;
        actor_zeta::environment::group group_;

    };

    struct abstract_service_unmanaged: public abstract_service {

        virtual ~abstract_service_unmanaged()                               = default;

        void input(service &s);

        void output(service &s);

        auto input() const -> const std::string&;

        auto output() const -> const std::string&;

        virtual bool send(msg&&);

        virtual void join(service &s);

    protected:
        template <typename F>
        void add(const std::string& name, F&&f){
            method_table.emplace(name,std::forward<F>(f));
        }
        std::string input_;
        std::string output_;
        std::unordered_map<std::string,method> method_table;
        std::unordered_map<std::string,service> services;
    };




}

