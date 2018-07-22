#include <QDataStream>
#include <QDebug>
#include <QFile>

#include "dummy/layer.h"
#include "dummy/map.h"


Dummy::Map::Map(quint16 width, quint16 height)
    : m_version(0x0001), m_width(width), m_height(height),
      m_firstLayer(m_width, m_height),
      m_secondLayer(m_width, m_height),
      m_thirdLayer(m_width, m_height)
{
    if (m_width < 1 || m_height < 1) {
        // Throw an exception.
    }
}

Dummy::Map::~Map() {
}

Dummy::Map&&
Dummy::Map::loadFromFile(const QString& filename) {
    Q_UNUSED(filename);
    return std::move(Map(2, 3));
}

void Dummy::Map::saveToFile(const QString& filename) {
    QFile file(filename);

    saveToFile(file);
}

void Dummy::Map::saveToFile(QFile& file) {
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out << m_version << m_width << m_height << m_chipset << m_music
        << m_firstLayer << m_secondLayer << m_thirdLayer;
}
