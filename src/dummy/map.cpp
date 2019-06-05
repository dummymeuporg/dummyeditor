#include <memory>

#include <QDataStream>
#include <QDebug>
#include <QFile>

#include "dummy/project.hpp"
#include "dummy/layer.hpp"
#include "dummy/map.hpp"

//Dummy::Map::Map() : Dummy::Map::Map(1, 1) {}

Dummy::Map::Map(const Project& project, quint16 width, quint16 height)
    : m_project(project), m_version(0x0001), m_width(width), m_height(height),
      m_firstLayer(m_width, m_height),
      m_secondLayer(m_width, m_height),
      m_thirdLayer(m_width, m_height),
      m_fourthLayer(m_width, m_height),
      m_blockingLayer(m_width * 2, m_height * 2)
{
    if (m_width < 1 || m_height < 1) {
        // Throw an exception.
    }
}

Dummy::Map::~Map() {
}

std::shared_ptr<Dummy::Map>
Dummy::Map::loadMap(const Dummy::Project& project, const QString& mapName) {

    QString baseDirectory(project.fullpath() + "/maps/");
    QFile graphicFile(baseDirectory + mapName + ".map");

    std::shared_ptr<Dummy::Map> map(loadGraphicLayersFromFile(
        project,
        graphicFile
    ));

    QFile blockingFile(baseDirectory + mapName + ".blk");
    map->_loadBlokingLayerFromFile(blockingFile);

    return map;
}

std::shared_ptr<Dummy::Map>
Dummy::Map::loadGraphicLayersFromFile(
        const Dummy::Project& project,
        QFile& file
)
{
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    std::shared_ptr<Dummy::Map> map(new Map(project));
    in >> *map;
    return map;
}

void Dummy::Map::_loadBlokingLayerFromFile(QFile& file)
{
    quint32 magicWord;

    file.open(QIODevice::ReadOnly);

    QDataStream in(&file);
    in.setByteOrder(QDataStream::LittleEndian);

    in >> magicWord;
    if (magicWord != Dummy::Map::BLOCKING_MAGIC_WORD) {
        throw WrongMagicNumber();
    }

    m_blockingLayer.resizeMap(m_width * 2, m_height * 2);
    in >> m_blockingLayer;


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
    if (magicWord != Dummy::Map::GRAPHIC_MAGIC_WORD)
    {
        throw WrongMagicNumber();
    }
    stream >> m_version >> m_width >> m_height;

    // read chipset and music from standard strings
    quint32 size;
    std::string name;

    stream >> size;
    if (0 != size) {
        name.resize(size);
        stream.readRawData(name.data(), static_cast<int>(size));
        m_chipset = QString::fromStdString(name);
    } else {
        m_chipset = "";
    }

    stream >> size;
    if (0 != size) {
        name.resize(size);
        stream.readRawData(name.data(), static_cast<int>(size));
        m_music = QString::fromStdString(name);
    } else {
        m_music = "";
    }

    m_firstLayer.resizeMap(m_width, m_height);
    m_secondLayer.resizeMap(m_width, m_height);
    m_thirdLayer.resizeMap(m_width, m_height);
    m_fourthLayer.resizeMap(m_width, m_height);


    stream >> m_firstLayer;
    stream >> m_secondLayer;
    stream >> m_thirdLayer;
    stream >> m_fourthLayer;
    //stream >> m_blockingLayer;
}

void Dummy::Map::_writeGraphicLayersToStream(QDataStream& stream) const {
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << Dummy::Map::GRAPHIC_MAGIC_WORD << m_version << m_width
           << m_height;


    // Write standard strings for chipset and music.
    std::string name = m_chipset.toStdString();

    /*
    quint32 size = static_cast<quint32>(name.size());
    stream << size;
    */

    // Apparently, the data() method returns the string size plus its content.
    stream.writeBytes(name.data(), static_cast<quint32>(name.size()));

    name = m_music.toStdString();
    //size = static_cast<quint32>(name.size());

    //stream << size;
    stream.writeBytes(name.data(), static_cast<quint32>(name.size()));

    stream << m_firstLayer
           << m_secondLayer
           << m_thirdLayer
           << m_fourthLayer;
           //<< m_blockingLayer;
}

void Dummy::Map::save() const {
    QString baseDirectory(m_project.fullpath() + "/maps/");
    QFile graphicFile(baseDirectory + m_name + ".map");
    graphicFile.open(QIODevice::WriteOnly);
    QDataStream out(&graphicFile);
    out.setByteOrder(QDataStream::LittleEndian);
    _writeGraphicLayersToStream(out);
    graphicFile.close();

    // XXX: Me lazy.
    qDebug() << "Write blocking layer.";
    QFile blockingFile(baseDirectory + m_name + ".blk");
    blockingFile.open(QIODevice::WriteOnly);

    QDataStream blkOut(&blockingFile);
    blkOut.setByteOrder(QDataStream::LittleEndian);
    blkOut << BLOCKING_MAGIC_WORD << m_blockingLayer;
    blockingFile.close();

}

Dummy::Layer&
Dummy::Layer::setTile(quint16 x, quint16 y, qint16 chipsetX, qint16 chipsetY)
{
    quint16 index = y * m_width + x;
    operator[](index) = std::make_tuple(chipsetX, chipsetY);
    return *this;
}

