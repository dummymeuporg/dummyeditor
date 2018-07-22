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

    private:
        quint16 m_width, m_height;
    };

}

QDataStream& operator<<(QDataStream& stream, const Dummy::Layer& layer);

#endif // LAYER_H
