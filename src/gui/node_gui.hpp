#ifndef GUI_NODE_GUI_HPP_
#define GUI_NODE_GUI_HPP_

#include <array>
#include <cmath>
#include <string>

#include "constants.hpp"
#include "raylib.h"
#include "utils.hpp"

namespace gui {

template<typename T>
class GuiNode {
private:
    T m_value{};
    Color m_color{BLACK};

    Vector2 m_pos{constants::sidebar_width +
                      static_cast<float>(constants::scene_width -
                                         constants::sidebar_width) /
                          2,
                  0};
    static constexpr float eps = 1e-3;
    const char* m_label{};

public:
    static constexpr int radius = 20;

    explicit GuiNode(const T& value);

    void render();
    void set_pos(Vector2 pos);
    [[nodiscard]] Vector2 get_pos() const;
    void set_color(Color color);
    void set_value(const T& value);
    T& get_value();
    void set_label(const char* label);
};

template<typename T>
GuiNode<T>::GuiNode(const T& value) : m_value{value} {}

template<typename T>
void GuiNode<T>::render() {
    constexpr int label_font_size = 25;
    constexpr int label_font_spacing = 2;
    const std::string value = std::to_string(m_value);

    const Vector2 value_size =
        utils::MeasureText(value.c_str(), label_font_size, label_font_spacing);

    const Vector2 value_pos{m_pos.x - value_size.x / 2,
                            m_pos.y - value_size.y / 2};

    const Vector2 label_size =
        utils::MeasureText(m_label, label_font_size, label_font_spacing);

    const Vector2 label_pos{m_pos.x - label_size.x / 2,
                            m_pos.y - 2 * label_size.y};

    DrawCircleV(m_pos, radius, m_color);
    utils::DrawText(value.c_str(), value_pos, WHITE, label_font_size,
                    label_font_spacing);

    utils::DrawText(m_label, label_pos, RED, label_font_size,
                    label_font_spacing);
}

template<typename T>
void GuiNode<T>::set_color(Color color) {
    m_color = color;
}

template<typename T>
void GuiNode<T>::set_value(const T& value) {
    m_value = value;
}

template<typename T>
T& GuiNode<T>::get_value() {
    return m_value;
}

template<typename T>
void GuiNode<T>::set_pos(Vector2 pos) {
    m_pos = pos;
}

template<typename T>
Vector2 GuiNode<T>::get_pos() const {
    return m_pos;
}

template<typename T>
void GuiNode<T>::set_label(const char* label) {
    m_label = label;
}

}  // namespace gui

#endif  // GUI_NODE_GUI_HPP_
