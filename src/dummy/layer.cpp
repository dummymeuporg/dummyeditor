#include <QDebug>
#include <QDataStream>
#include <QtGlobal>

#include "dummy/layer.hpp"

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

void Dummy::Layer::_loadFromStream(QDataStream& stream) {
    stream.setByteOrder(QDataStream::LittleEndian);
    for (auto it = begin(); it != end(); ++it) {
        quint16 i, j;
        stream >> i >> j;
        *it = std::make_tuple(i, j);
    }
}

void Dummy::Layer::_writeToStream(QDataStream& stream) const {
    stream.setByteOrder(QDataStream::LittleEndian);
    for (auto it = begin(); it != end(); ++it) {
        qDebug() << std::get<0>(*it) << std::get<1>(*it);
        stream << std::get<0>(*it) << std::get<1>(*it);
    }
}
