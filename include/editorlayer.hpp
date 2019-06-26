#pragma once

#include <cstdint>
#include <vector>

namespace Dummy {
namespace Core {
using GraphicLayer = std::vector<std::pair<std::int8_t, std::int8_t>>;
} // namespace Core
} // namespace Dummy

class EditorLayer {
public:
    EditorLayer(const Dummy::Core::GraphicLayer&);
    bool visible() {
        return m_visible;
    }
    void setVisible(bool visible);
private:
    bool m_visible;
    const Dummy::Core::GraphicLayer& m_layer;
};
