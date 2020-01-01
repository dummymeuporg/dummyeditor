#ifndef EDITORGRAPHICLAYER_H
#define EDITORGRAPHICLAYER_H

#include <cstdint>
#include <vector>

#include "editor/layer.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Dummy {
namespace Core {
class GraphicLayer;
} // namespace Core
} // namespace Dummy

namespace Editor {

//////////////////////////////////////////////////////////////////////////////
//  GraphicLayer class
//////////////////////////////////////////////////////////////////////////////

class GraphicLayer : public Layer {
public:
    GraphicLayer(Dummy::Core::GraphicLayer&);

    Dummy::Core::GraphicLayer& layer() { return m_layer; }
    std::pair<std::int8_t, std::int8_t>& operator[](std::size_t index);

    std::uint16_t width() const;
    std::uint16_t height() const;

private:
    Dummy::Core::GraphicLayer& m_layer;

};

} // namespace Editor

#endif // EDITORGRAPHICLAYER_H
