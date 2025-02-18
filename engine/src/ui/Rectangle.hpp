#pragma once

#include "ui/Shape.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Birdy3d {

    class Rectangle : public Shape {
    public:
        Rectangle(UIVector pos, UIVector size, Color::Name color = Color::Name::WHITE, Type type = FILLED, Placement placement = Placement::BOTTOM_LEFT);
        ~Rectangle();
        void draw(glm::mat4 move) override;
        bool contains(glm::vec2 point) override;

    private:
        void create_buffers();
        void update_values();
    };

}
