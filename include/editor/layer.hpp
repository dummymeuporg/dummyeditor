#pragma once

namespace Editor {
class Layer {
public:
    Layer();
    bool visible() {
        return m_visible;
    }
    void setVisible(bool visible);
private:
    bool m_visible;
};
} // namespace Editor
