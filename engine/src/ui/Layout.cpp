#pragma once

#include "ui/Layout.hpp"
#include "ui/Shape.hpp"
#include "ui/TextRenderer.hpp"

namespace Birdy3d {

    Layout::Layout(UIVector pos, UIVector size, Placement placement, Theme* theme, std::string name)
        : Widget(pos, size, placement, theme, name) { }

    void Layout::addChild(Widget* w) {
        children.push_back(w);
    }

    void Layout::draw() {
        if (hidden)
            return;
        Widget::draw();
        for (Widget* w : children) {
            w->draw();
        }
    }

    void Layout::lateUpdate() {
        for (std::vector<Widget*>::reverse_iterator it = children.rbegin(); it != children.rend(); it++) {
            (*it)->lateUpdate();
        }

        Widget::lateUpdate();
    }

    bool Layout::onScroll(InputScrollEvent* event, bool hover) {
        for (std::vector<Widget*>::reverse_iterator it = children.rbegin(); it != children.rend(); it++) {
            if ((*it)->_onScroll(event, hover))
                hover = false;
        }

        return !hover;
    }

    bool Layout::onClick(InputClickEvent* event, bool hover) {
        for (std::vector<Widget*>::reverse_iterator it = children.rbegin(); it != children.rend(); it++) {
            if ((*it)->_onClick(event, hover))
                hover = false;
        }

        return !hover;
    }

    bool Layout::onKey(InputKeyEvent* event, bool hover) {
        for (std::vector<Widget*>::reverse_iterator it = children.rbegin(); it != children.rend(); it++) {
            if ((*it)->_onKey(event, hover))
                hover = false;
        }

        return !hover;
    }

    bool Layout::onChar(InputCharEvent* event, bool hover) {
        for (std::vector<Widget*>::reverse_iterator it = children.rbegin(); it != children.rend(); it++) {
            if ((*it)->_onChar(event, hover))
                hover = false;
        }

        return !hover;
    }

    bool Layout::update(bool hover) {
        for (std::vector<Widget*>::reverse_iterator it = children.rbegin(); it != children.rend(); it++) {
            if ((*it)->_update(hover))
                hover = false;
        }

        return !hover;
    }

}
