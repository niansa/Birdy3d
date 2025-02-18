#pragma once

#include "ui/Layout.hpp"
#include "ui/Widget.hpp"

namespace Birdy3d {

    class AbsoluteLayout : public Layout {
    public:
        void arrange(const std::list<std::shared_ptr<Widget>>& children, glm::vec2 pos, glm::vec2 size) const override {
            for (const auto& child : children) {
                glm::vec2 child_size = child->preferred_size(size);
                glm::vec2 child_pos = pos + child->preferred_position(size, child_size);
                if (child_size.x == 0 || child_size.y == 0)
                    child_size = size;
                child->arrange(child_pos, child_size);
            }
        }

        glm::vec2 minimal_size(const std::list<std::shared_ptr<Widget>>& children [[maybe_unused]]) const override {
            return glm::vec2(0);
        }
    };

}
