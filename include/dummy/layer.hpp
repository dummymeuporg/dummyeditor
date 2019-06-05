#ifndef LAYER_H
#define LAYER_H

#include <cstdint>

#include <QDataStream>
#include <QtGlobal>
#include <QVector>

#include <tuple>

namespace Dummy {
    class Layer : public QVector<std::tuple<std::int8_t, std::int8_t>>
    {
    public:
        Layer(quint16, quint16);

        void reset();

        void resizeMap(quint16, quint16);

        friend QDataStream& operator>>(QDataStream& stream,
                                       Dummy::Layer& layer) {
            layer._loadFromStream(stream);
            return stream;
        }

        friend QDataStream& operator<<(QDataStream& stream,
                                       const Dummy::Layer& layer) {
            layer._writeToStream(stream);
            return stream;
        }

        Layer& setTile(quint16 x, quint16 y,
                       std::int8_t chipsetX, std::int8_t chipsetY);

    private:
        void _writeToStream(QDataStream&) const;
        void _loadFromStream(QDataStream&);

        quint16 m_width, m_height;
    };

}

#endif // LAYER_H
