#include <QDataStream>
#include <QtGlobal>

#include "layer.h"

Dummy::Layer::Layer(quint16 width, quint16 height) :
    QVector<std::tuple<qint16, qint16>>(width * height),
    m_width(width), m_height(height)
{
    reset();
}

void Dummy::Layer::reset() {
    for (auto it = begin(); it != end(); ++it) {
        *it = std::make_tuple(-1, -1);
    }
}

void Dummy::Layer::resizeMap(quint16 width, quint16 height) {
    m_width = width;
    m_height = height;
    resize(m_width * m_height);
}

QDataStream& operator<<(QDataStream& stream, const Dummy::Layer& layer) {
    for (auto it = layer.begin(); it != layer.end(); ++it) {
        stream << std::get<0>(*it) << std::get<1>(*it);
    }
    return stream;
}

void _loadFromStream(QDataStream& stream, Dummy::Layer& layer) {
    for (auto it = layer.begin(); it != layer.end(); ++it) {
        quint16 i, j;
        stream >> i >> j;
        *it = std::make_tuple(i, j);
    }
}
