#pragma once

#include "core/Base.hpp"
#include "render/Material.hpp"
#include "render/Mesh.hpp"

struct aiMesh;
struct aiNode;
struct aiScene;

namespace Birdy3d {

    class Entity;

    class Model {
    public:
        Model(const std::string& path);
        Model(std::unique_ptr<Mesh>);
        Model(std::vector<std::unique_ptr<Mesh>>&);
        void render(Entity& entity, const Material* material, const Shader& shader, bool transparent) const;
        void render_depth(Entity&, const Shader&) const;
        void render_wireframe(Entity&, const Shader&) const;
        const std::vector<std::unique_ptr<Mesh>>& get_meshes() const;
        std::pair<glm::vec3, glm::vec3> bounding_box() const { return m_bounding_box; }

    private:
        std::vector<std::unique_ptr<Mesh>> m_meshes;
        std::string m_directory;
        Material m_embedded_material;
        std::pair<glm::vec3, glm::vec3> m_bounding_box;

        void load(std::string path);
        void process_node(aiNode* node, const aiScene* scene);
        std::unique_ptr<Mesh> process_mesh(aiMesh* mesh, const aiScene* scene);
        void compute_bounding_box();
    };

}
