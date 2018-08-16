#include "blockinglayer.h"
#include <QDataStream>
#include <QDebug>
#include <QtGlobal>

Dummy::BlockingLayer::BlockingLayer(quint16 width, quint16 height) :
    QVector<bool>(width * height), m_width(width), m_height(height)
{
    qDebug() << width << height;
    reset();
}

void Dummy::BlockingLayer::reset()
{
    for (auto it = begin(); it != end(); ++it)
    {
        *it = false; // Not blocking.
    }
}

void Dummy::BlockingLayer::resizeMap(quint16 width, quint16 height)
{
    m_width = width;
    m_height = height;
    resize(m_width * m_height);
}

void Dummy::BlockingLayer::_loadFromStream(QDataStream& stream)
{
    for (auto it = begin(); it != end(); ++it)
    {
        bool isBlocking;
        stream >> isBlocking;
        *it = isBlocking;
    }
}

void Dummy::BlockingLayer::_writeToStream(QDataStream& stream) const
{
    for (auto it = begin(); it != end(); ++it)
    {
        stream << *it;
    }
}
