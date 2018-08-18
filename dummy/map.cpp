#include <QDataStream>
#include <QDebug>
#include <QFile>

#include "dummy/layer.h"
#include "dummy/map.h"

//Dummy::Map::Map() : Dummy::Map::Map(1, 1) {}

Dummy::Map::Map(const Project& project, quint16 width, quint16 height)
    : m_project(project), m_version(0x0001), m_width(width), m_height(height),
      m_firstLayer(m_width, m_height),
      m_secondLayer(m_width, m_height),
      m_thirdLayer(m_width, m_height),
      m_fourthLayer(m_width, m_height),
      m_blockingLayer(m_width, m_height)
{
    if (m_width < 1 || m_height < 1) {
        // Throw an exception.
    }
}

Dummy::Map::~Map() {
}

std::shared_ptr<Dummy::Map>
Dummy::Map::loadFromFile(const Dummy::Project& project,
                         const QString& filename) {

    QFile file(filename);

    return loadFromFile(project, file);
}

std::shared_ptr<Dummy::Map>
Dummy::Map::loadFromFile(const Dummy::Project& project, QFile& file) {
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    std::shared_ptr<Dummy::Map> map(new Map(project));
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
    quint32 magicWord;

    stream.setByteOrder(QDataStream::LittleEndian);
    stream >> magicWord;
    if (magicWord != Dummy::Map::MAGIC_WORD)
    {
        // XXX: Throw an exception?
    }
    stream >> m_version >> m_width >> m_height >> m_chipset >> m_music;

    m_firstLayer.resizeMap(m_width, m_height);
    m_secondLayer.resizeMap(m_width, m_height);
    m_thirdLayer.resizeMap(m_width, m_height);
    m_fourthLayer.resizeMap(m_width, m_height);
    m_blockingLayer.resizeMap(m_width, m_height);

    stream >> m_firstLayer;
    stream >> m_secondLayer;
    stream >> m_thirdLayer;
    stream >> m_fourthLayer;
    stream >> m_blockingLayer;
}

void Dummy::Map::_writeToStream(QDataStream& stream) const {
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << Dummy::Map::MAGIC_WORD << m_version << m_width
           << m_height << m_chipset << m_music
           << m_firstLayer
           << m_secondLayer
           << m_thirdLayer
           << m_fourthLayer
           << m_blockingLayer;
}

Dummy::Layer&
Dummy::Layer::setTile(quint16 x, quint16 y, qint16 chipsetX, qint16 chipsetY)
{
    quint16 index = y * m_width + x;
    operator[](index) = std::make_tuple(chipsetX, chipsetY);
    return *this;
}
