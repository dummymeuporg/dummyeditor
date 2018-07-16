#include <QDataStream>
#include <QFile>

#include "map.h"

Dummy::Map::Map(quint16 width, quint16 height)
    : m_version(0x0001), m_width(width), m_height(height),
      firstLayer(nullptr), secondLayer(nullptr),
      thirdLayer(nullptr)
{
    if (m_width < 1 || m_height < 0) {
        // Throw an exception.
    }
    firstLayer = std::shared_ptr<int>(new int[m_width * m_height * 2]);
    secondLayer = std::shared_ptr<int>(new int[m_width * m_height * 2]);
    thirdLayer = std::shared_ptr<int>(new int[m_width * m_height * 2]);
}

Dummy::Map::~Map() {
    firstLayer.reset();
    secondLayer.reset();
    thirdLayer.reset();
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
    out << m_version << m_width << m_height << m_chipset << m_music;
}
