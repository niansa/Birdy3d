#include "ui/Rectangle.hpp"

#include "core/RessourceManager.hpp"
#include "render/Shader.hpp"
#include "ui/Canvas.hpp"
#include "ui/Theme.hpp"
#include <glad/glad.h>

namespace Birdy3d {

    Rectangle::Rectangle(UIVector pos, UIVector size, Color::Name color, Type type, Placement placement)
        : Shape(pos, size, color, placement) {
        this->type = type;
    }

    Rectangle::~Rectangle() {
        glDeleteBuffers(1, &m_vbo);
        glDeleteVertexArrays(1, &m_vao);
    }

    void Rectangle::draw(glm::mat4 move) {
        if (m_hidden)
            return;

        if (!m_vao || !m_vbo)
            create_buffers();

        if (m_dirty) {
            m_dirty = false;
            update_values();
        }

        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture);
        m_shader->use();
        m_shader->set_int("type", type);
        m_shader->set_mat4("projection", projection());
        m_shader->set_mat4("move", move);
        m_shader->set_mat4("move_self", m_move_self);
        m_shader->set_vec4("color", Application::theme->color(m_color));
        m_shader->set_int("rectTexture", 0);
        glBindVertexArray(m_vao);
        if (type == Shape::OUTLINE)
            glDrawArrays(GL_LINE_LOOP, 0, 4);
        else
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    bool Rectangle::contains(glm::vec2 point) {
        glm::vec2 bottom_left = UIVector::get_relative_position(m_position, m_size, m_parentSize, m_placement);
        glm::vec2 size = m_size.to_pixels(m_parentSize);
        glm::vec2 top_right = bottom_left + size;
        return point.x > bottom_left.x && point.x < top_right.x && point.y > bottom_left.y && point.y < top_right.y;
    }

    void Rectangle::create_buffers() {
        float vertices[4 * 4];
        // Create buffers
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        // Write to buffers
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
        // vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        // vertex colors
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    }

    void Rectangle::update_values() {
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glm::vec2 pos = UIVector::get_relative_position(m_position, m_size, m_parentSize, m_placement);
        glm::vec2 size = m_size.to_pixels(m_parentSize);
        m_move_self = glm::mat4(1);
        m_move_self = glm::translate(m_move_self, glm::vec3(pos + glm::vec2(size.x / 2, size.y / 2), 0.0f));
        if (m_rotation != 0)
            m_move_self = glm::rotate(m_move_self, m_rotation, glm::vec3(0, 0, 1));
        m_move_self = glm::scale(m_move_self, glm::vec3(size, 1.0f));
        float ua = m_texCoordA.x;
        float va = m_texCoordA.y;
        float ub = m_texCoordB.x;
        float vb = m_texCoordB.y;
        // clang-format off
        if (type == Shape::OUTLINE) {
            float vertices[] = {
                -0.5, -0.5, ua, va,
                -0.5,  0.5, ua, vb,
                 0.5,  0.5, ub, vb,
                 0.5, -0.5, ub, va
            };
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices[0]);
        } else {
            float vertices[] = {
                -0.5, -0.5, ua, vb,
                 0.5, -0.5, ub, vb,
                -0.5,  0.5, ua, va,
                 0.5,  0.5, ub, va
            };
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices[0]);
        }
        // clang-format on
    }

}
