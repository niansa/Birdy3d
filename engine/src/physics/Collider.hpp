#pragma once

#include "events/EventBus.hpp"
#include "physics/ConvexMeshGenerators.hpp"
#include "scene/Component.hpp"
#include <glm/glm.hpp>
#include <vector>

namespace Birdy3d {

    class CollisionPoints;
    class Mesh;
    class Model;

    class Collider : public Component {
    public:
        Collider(Model*);
        Collider(GenerationMode);
        void start() override;
        CollisionPoints collides(Collider&);
        void render_wireframe(Shader&);

    private:
        Model* m_model;
        GenerationMode m_generation_mode;
        glm::vec3 m_points[4];
        int m_point_count;

        bool collides(const Mesh& mesh_a, const Mesh& mesh_b, const glm::mat4 transform_a, const glm::mat4 transform_b);
        glm::vec3 support(const Mesh& a, const Mesh& b, const glm::mat4 transform_a, const glm::mat4 transform_b, glm::vec3 direction);
        bool line(glm::vec3& direction);
        bool triangle(glm::vec3& direction);
        bool tetrahedron(glm::vec3& direction);
        bool sameDirection(glm::vec3 a, glm::vec3 b);
        void push_front(glm::vec3 point);
        bool nextSimplex(glm::vec3& direction);
    };

}
