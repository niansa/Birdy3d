#pragma once

#include "core/Application.hpp"
#include "ui/Widget.hpp"
#include "ui/widgets/AbsoluteLayout.hpp"

namespace Birdy3d {

    class Canvas : public AbsoluteLayout {
    public:
        bool updated = false;

        Canvas()
            : AbsoluteLayout(0_px, 100_p) {
                Application::eventBus->subscribe(this, &Canvas::onScroll);
                Application::eventBus->subscribe(this, &Canvas::onClick);
                Application::eventBus->subscribe(this, &Canvas::onKey);
                Application::eventBus->subscribe(this, &Canvas::onChar);
            };

        void update() {
            if (!hidden) {
                updated = true;
                glm::vec2 viewport = Application::getViewportSize();
                AbsoluteLayout::notifyEvent(EventType::UPDATE, nullptr, true);
                AbsoluteLayout::lateUpdate();
                AbsoluteLayout::arrange(glm::vec2(0), viewport);
            }
        }

        void draw() override {
            if (updated)
                AbsoluteLayout::draw();
        }

    private:
        void onScroll(InputScrollEvent* event) {
            Layout::notifyEvent(EventType::SCROLL, event, true);
        }

        void onClick(InputClickEvent* event) {
            Layout::notifyEvent(EventType::CLICK, event, true);
        }

        void onKey(InputKeyEvent* event) {
            Layout::notifyEvent(EventType::KEY, event, true);
        }

        void onChar(InputCharEvent* event) {
            Layout::notifyEvent(EventType::CHAR, event, true);
        }
    };

}
