#pragma once

#include "core/Base.hpp"
#include "ecs/Entity.hpp"
#include "physics/PhysicsWorld.hpp"

namespace Birdy3d {

    class Camera;

    class Scene : public Entity {
    public:
        std::weak_ptr<Camera> main_camera;
        Camera* m_current_camera = nullptr;

        Scene(std::string name = "Scene");
        void start() override;
        void update() override;
        void serialize(serializer::Adapter&) override;

    private:
        std::unique_ptr<PhysicsWorld> m_physics_world;

        BIRDY3D_REGISTER_TYPE_DEC(Scene);
    };

}
