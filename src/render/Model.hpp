#ifndef BIRDY3D_MODEL_HPP
#define BIRDY3D_MODEL_HPP

#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Mesh.hpp"
#include "../objects/Component.hpp"
#include "../objects/GameObject.hpp"

class Model : public Component {
public:
    Model(GameObject *o, std::string path, bool useTexture = true, glm::vec4 color = glm::vec4(0.0f), glm::vec3 specular = glm::vec3(1.0f), glm::vec3 emissive = glm::vec3(0.0f)) : Component(o) {
        this->path = path;
        this->useTexture = useTexture;
        this->color = color;
        this->specular = specular;
        this->emissive = emissive;
    }
    void draw(Shader shader);
    void cleanup() override;
    void start() override;
    void update(float deltaTime) override;

private:
    std::string path;
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded;
    bool useTexture;
    glm::vec4 color;
    glm::vec3 specular;
    glm::vec3 emissive;

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif