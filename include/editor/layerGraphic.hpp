#ifndef EDITORGRAPHICLAYER_H
#define EDITORGRAPHICLAYER_H

#include <cstdint>
#include <vector>

#include "dummy/core/layer.hpp"
#include "editor/layer.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Editor {

//////////////////////////////////////////////////////////////////////////////
//  GraphicLayer class
//////////////////////////////////////////////////////////////////////////////

class GraphicLayer : public Layer
{
public:
    explicit GraphicLayer(Dummy::Core::GraphicLayer&);

    Dummy::Core::GraphicLayer& layer() { return m_layer; }
    tileaspect at(tilecoords coords) { return m_layer.at(coords); }
    void set(tilecoords coords, tileaspect val) { m_layer.set(coords, val); }

    std::uint16_t width() const;
    std::uint16_t height() const;

private:
    Dummy::Core::GraphicLayer& m_layer;
};

} // namespace Editor

#endif // EDITORGRAPHICLAYER_H
