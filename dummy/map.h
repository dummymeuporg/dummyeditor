#ifndef _DUMMY_MAP_H
#define _DUMMY_MAP_H

#include <QString>
#include <QtGlobal>
#include <memory>

class QFile;

namespace Dummy {

    class Map
    {
    public:
        Map();
        Map(quint16 width = 1, quint16 height = 1);
        virtual ~Map();

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

        static Map&& loadFromFile(const QString& filename);
        void saveToFile(const QString& filename);
        void saveToFile(QFile& file);

    private:
        unsigned short m_version;
        QString m_name;
        quint16 m_width, m_height; // Map dimension
        QString m_chipset;
        QString m_music;
        QString m_backgroundPicture;
        std::shared_ptr<int> firstLayer;
        std::shared_ptr<int> secondLayer;
        std::shared_ptr<int> thirdLayer;
    };
}

#endif // _DUMMY_MAP_H
