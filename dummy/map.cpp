#include <QDataStream>
#include <QDebug>
#include <QFile>

#include "dummy/layer.h"
#include "dummy/map.h"

Dummy::Map::Map() : Dummy::Map::Map(1, 1) {}

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

std::shared_ptr<Dummy::Map>
Dummy::Map::loadFromFile(const QString& filename) {

    QFile file(filename);

    return loadFromFile(file);
}

std::shared_ptr<Dummy::Map>
Dummy::Map::loadFromFile(QFile& file) {
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    std::shared_ptr<Dummy::Map> map(new Map());
    in >> *map;
    return map;
}

void Dummy::Map::saveToFile(const QString& filename) const {
    QFile file(filename);

    saveToFile(file);
}

void Dummy::Map::saveToFile(QFile& file) const {
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out << *this;
}

void Dummy::Map::_loadFromStream(QDataStream& stream) {
    stream >> m_version >> m_width >> m_height >> m_chipset >> m_music;

    m_firstLayer.resizeMap(m_width, m_height);
    m_secondLayer.resizeMap(m_width, m_height);
    m_thirdLayer.resizeMap(m_width, m_height);
}

void Dummy::Map::_writeToStream(QDataStream & stream) const {
    stream << m_version << m_width << m_height
           << m_chipset << m_music
           << m_firstLayer << m_secondLayer << m_firstLayer;
}
