#include "Mesh.hpp"
#include <glm/glm.hpp>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    this->useTexture = true;

    setupMesh();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, glm::vec4 color, glm::vec3 specular, glm::vec3 emissive) {
    this->vertices = vertices;
    this->indices = indices;
    this->color = color;
    this->specular = specular;
    this->emissive = emissive;
    this->useTexture = false;

    setupMesh();
}

void Mesh::setupMesh() {
    // generate VAO, VBO and EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    
    // load vertices into VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    // load indices into EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // inform OpenGL how to interpret the vertex data inside the VBO
    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

    glBindVertexArray(0);
}

void Mesh::draw(Shader *shader) {
    shader->setBool("useTexture", useTexture);
    if (useTexture) {
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;
        unsigned int emissiveNr = 1;
        for(unsigned int i = 0; i < textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
            // retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = textures[i].type;
            if(name == "texture_diffuse")              // diffuse map -> normal texture
                number = std::to_string(diffuseNr++);
            else if(name == "texture_specular")        // specular map -> light intensity
                number = std::to_string(specularNr++);
            else if(name == "texture_normal")          // normal map -> stores normals, used to create smooth surfaces
                number = std::to_string(normalNr++);
            else if(name == "texture_height")          // height map -> store height information
                number = std::to_string(heightNr++);
            else if(name == "texture_emissive")        // emission map -> emit light (does not illuminate other objects)
                number = std::to_string(normalNr++);

            shader->setFloat(("material." + name + number).c_str(), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }
        if (specularNr > 1)
            shader->setBool("hasSpecular", true);
        if (emissiveNr > 1)
            shader->setBool("hasEmissive", true);
        glActiveTexture(GL_TEXTURE0);
    } else {
        shader->setBool("hasSpecular", true);
        shader->setBool("hasEmissive", true);
        shader->setVec4("material.color", this->color);
        shader->setVec3("material.specular", this->specular);
        shader->setVec3("material.emissive", this->emissive);
    }
    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::renderDepth() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::cleanup() {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}