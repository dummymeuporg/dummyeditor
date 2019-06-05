#pragma once

#include <exception>

#include <QVector>
#include <QString>
#include <QtGlobal>
#include <memory>

#include "dummy/layer.hpp"
#include "dummy/blockinglayer.hpp"

class QDataStream;
class QFile;

namespace Dummy {

    class Project;

    class MapError : public std::exception {
    };

    class WrongMagicNumber : public MapError
    {
    public:
        const char* what() const noexcept {
            return "the magic number is invalid";
        }
    };

    class Map
    {
        const quint32 GRAPHIC_MAGIC_WORD = 0xF000BABA;
        const quint32 BLOCKING_MAGIC_WORD = 0xDEADDAAD;
    public:
        Map(const Project& project, quint16 width = 1, quint16 height = 1);
        virtual ~Map();

        inline const Project& project() const {
            return m_project;
        }

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

        inline Layer& firstLayer() {
            return m_firstLayer;
        }

        inline Layer& secondLayer() {
            return m_secondLayer;
        }

        inline Layer& thirdLayer() {
            return m_thirdLayer;
        }

        inline Layer& fourthLayer() {
            return m_fourthLayer;
        }

        BlockingLayer& blockingLayer() {
            return m_blockingLayer;
        }

        static std::shared_ptr<Map> loadMap(const Project&, const QString&);
        static std::shared_ptr<Map> loadGraphicLayersFromFile(
            const Project&,
                QFile& file
        );
        void _loadBlokingLayerFromFile(QFile&);

        void save() const;
        void saveToFile(const QString& filename) const;
        void saveToFile(QFile& file) const;

        friend QDataStream& operator<<(QDataStream& stream,
                                       const Dummy::Map& map) {
            map._writeGraphicLayersToStream(stream);
            return stream;
        }

        friend QDataStream& operator>>(QDataStream& stream,
                                       Dummy::Map& map) {
            map._loadFromStream(stream);
            return stream;
        }

    private:

        void _loadFromStream(QDataStream&);
        void _writeGraphicLayersToStream(QDataStream&) const;

        const Project& m_project;
        unsigned short m_version;
        QString m_name;
        quint16 m_width, m_height; // Map dimension
        QString m_chipset;
        QString m_music;
        QString m_backgroundPicture;
        Layer m_firstLayer, m_secondLayer, m_thirdLayer, m_fourthLayer;
        BlockingLayer m_blockingLayer;
    };
}
