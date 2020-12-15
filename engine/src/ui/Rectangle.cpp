#include "ui/Rectangle.hpp"

Rectangle::Rectangle(Shader *shader, glm::ivec2 pos, glm::ivec2 size, float depth, bool filled, glm::vec4 color) : shader(shader), pos(pos), size(size), depth(depth), filled(filled), color(color) {
    this->hasTexture = false;
    this->isText = false;
}

Rectangle::Rectangle(Shader *shader, glm::ivec2 pos, glm::ivec2 size, float depth, unsigned int textureID) : shader(shader), pos(pos), size(size), depth(depth), textureID(textureID) {
    this->hasTexture = true;
    this->filled = true;
    this->isText = false;
}

Rectangle::Rectangle(Shader *shader, glm::ivec2 pos, glm::ivec2 size, float depth, glm::vec4 textColor, unsigned int charTexture) : shader(shader), pos(pos), size(size), depth(depth), color(textColor), textureID(charTexture) {
    this->isText = true;
    this->filled = true;
}

glm::ivec2 Rectangle::getPos() {
    return this->pos;
}

glm::ivec2 Rectangle::getSize() {
    return this->size;
}

void Rectangle::resize(glm::ivec2 size) {
    if (this->size != size) {
        this->size = size;
        this->dirty = true;
    }
}

void Rectangle::setPos(glm::ivec2 pos) {
    if (this->pos != pos) {
        this->pos = pos;
        this->dirty = true;
    }
}

void Rectangle::setTexture(unsigned int textureID) {
    this->textureID = textureID;
}

void Rectangle::setColor(glm::vec4 color) {
    this->color = color;
}

void Rectangle::setDepth(float depth) {
    if (this->depth != depth) {
        this->depth = depth;
        this->dirty = true;
    }
}

void Rectangle::setMove(glm::mat4 move) {
    this->hasMatrix = true;
    this->move = move;
}

void Rectangle::draw() {
    if (!vao || !vbo)
        this->createBuffers();
    
    if (dirty) {
        dirty = false;
        this->updateVBO();
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->textureID);
    this->shader->use();
    this->shader->setBool("isText", this->isText);
    this->shader->setBool("hasTexture", this->hasTexture);
    this->shader->setBool("hasMatrix", this->hasMatrix);
    this->shader->setMat4("move", this->move);
    this->shader->setVec4("color", this->color);
    this->shader->setInt("rectTexture", 0);
    glBindVertexArray(this->vao);
    if (this->filled)
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    else
        glDrawArrays(GL_LINE_LOOP, 0, 4);
}

void Rectangle::createBuffers() {
    float vertices[4 * 5];
    // Create buffers
    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);
    // Write to buffers
    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    // vertex colors
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}

void Rectangle::updateVBO() {
    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    float x;
    float y;
    float w;
    float h;
    float d = this->depth;
    if (this->isText) {
        glm::vec2 viewportSize = Application::getViewportSize();
        float xratio = 2 / viewportSize.x;
        float yratio = 2 / viewportSize.y;
        x = this->pos.x * xratio - 1;
        y = this->pos.y * yratio - 1;
        w = this->size.x * xratio;
        h = this->size.y * yratio;
    } else {
        x = this->pos.x;
        y = this->pos.y;
        w = this->size.x;
        h = this->size.y;
    }
    if (this->filled) {
        float vertices[] = {
            x,     y,     d,  0.0f, 1.0f,
            x + w, y,     d,  1.0f, 1.0f,
            x,     y + h, d,  0.0f, 0.0f,
            x + w, y + h, d,  1.0f, 0.0f
        };
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices[0]);
    } else {
        float vertices[] = {
            x,     y,     d,  0.0f, 0.0f,
            x,     y + h, d,  0.0f, 1.0f,
            x + w, y + h, d,  1.0f, 1.0f,
            x + w, y,     d,  1.0f, 0.0f,
        };
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices[0]);
    }
}
