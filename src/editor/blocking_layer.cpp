#include "editor/blocking_layer.hpp"

namespace Editor {

BlockingLayer::BlockingLayer(Dummy::Core::BlockingLayer& layer)
    : m_layer(layer)
{}

} // namespace Editor
