#pragma once

#include <QVector>
#include <QString>
#include <QtGlobal>
#include <memory>

#include "dummy/layer.h"

class QDataStream;
class QFile;

namespace Dummy {

    class Map
    {
    public:
        Map();
        Map(quint16 width, quint16 height);
        virtual ~Map();

        inline unsigned short version() const {
            return m_version;
        }

        const QString& name() const {
            return m_name;
        }

        quint16 width() const {
            return m_width;
        }

        quint16 height() const {
            return m_height;
        }

        const QString& chipset() const {
            return m_chipset;
        }

        const QString& music() const {
            return m_music;
        }

        const QString& backgroundPicture() const {
            return m_backgroundPicture;
        }

        Map& setVersion(unsigned short version) {
            m_version = version;
            return *this;
        }

        Map& setName(const QString& name) {
            m_name = name;
            return *this;
        }

        Map& setWidth(quint16 width) {
            m_width = width;
            return *this;
        }

        Map& setHeight(quint16 height) {
            m_height = height;
            return *this;
        }

        Map& setChipset(const QString& chipset) {
            m_chipset = chipset;
            return *this;
        }

        Map& setMusic(const QString& music) {
            m_music = music;
            return *this;
        }

        Map& setBackgroundPicture(const QString& backgroundPicture) {
            m_backgroundPicture = backgroundPicture;
            return *this;
        }

        inline const Layer& firstLayer() const {
            return m_firstLayer;
        }

        inline const Layer& secondLayer() const {
            return m_secondLayer;
        }

        inline const Layer& thirdLayer() const {
            return m_thirdLayer;
        }

        static std::shared_ptr<Map> loadFromFile(const QString& filename);
        static std::shared_ptr<Map> loadFromFile(QFile& file);

        void saveToFile(const QString& filename) const;
        void saveToFile(QFile& file) const;

        friend QDataStream& operator<<(QDataStream& stream,
                                       const Dummy::Map& map) {
            map._writeToStream(stream);
            return stream;
        }

        friend QDataStream& operator>>(QDataStream& stream,
                                       Dummy::Map& map) {
            map._loadFromStream(stream);
            return stream;
        }


    private:

        void _loadFromStream(QDataStream&);
        void _writeToStream(QDataStream&) const;

        unsigned short m_version;
        QString m_name;
        quint16 m_width, m_height; // Map dimension
        QString m_chipset;
        QString m_music;
        QString m_backgroundPicture;
        Layer m_firstLayer, m_secondLayer, m_thirdLayer;
    };
}
