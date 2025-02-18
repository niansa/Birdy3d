#pragma once

#include "ui/TextRenderer.hpp"
#include "ui/Theme.hpp"
#include "ui/Widget.hpp"

namespace Birdy3d {

    class FPSCounter : public Widget {
    public:
        Text* text;

        FPSCounter(UIVector position, Placement placement)
            : Widget(position, 0_px, placement) {
            text = add_text(0_px, "FPS: ", Color::Name::FG, Placement::CENTER_LEFT);
        }

        void on_update() override {
            int fps = 1 / Application::delta_time;
            text->text("FPS: " + std::to_string(fps));
        }

        glm::vec2 minimal_size() override {
            glm::vec2 min_size = Application::theme->text_renderer().text_size("FPS: 000") + 2.0f;
            return glm::max(min_size, Widget::minimal_size());
        }
    };

}
