#pragma once

#include "core/Base.hpp"

namespace Birdy3d {

    class GameObject;

    class Component {
    public:
        GameObject* object = nullptr;

        virtual ~Component() = default;
        void _start();
        void _update();
        void _cleanup();
        bool loaded() const { return m_loaded; }
        void remove();
        template <class Archive>
        void serialize(Archive& ar) { }

    protected:
        bool m_loaded = false;

        virtual void start() {};
        virtual void update() {};
        virtual void cleanup() {};
    };

}
