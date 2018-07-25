#ifndef LAYER_H
#define LAYER_H

#include <QDataStream>
#include <QtGlobal>
#include <QVector>

#include <tuple>

namespace Dummy {
    class Layer : public QVector<std::tuple<qint16, qint16>>
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

    private:
        void _writeToStream(QDataStream&) const;
        void _loadFromStream(QDataStream&);

        quint16 m_width, m_height;
    };

}

#endif // LAYER_H
