#pragma once

#include <QVector>
#include <QtGlobal>

namespace Dummy {
    class BlockingLayer : public QVector<bool>
    {
    public:
        BlockingLayer(quint16, quint16);

        void reset();

        void resizeMap(quint16, quint16);

        friend QDataStream& operator>>(QDataStream& stream,
                                       Dummy::BlockingLayer& blockingLayer)
        {
            blockingLayer._loadFromStream(stream);
            return stream;
        }

        friend QDataStream& operator<<(QDataStream& stream,
                                       const BlockingLayer& blockingLayer)
        {
            blockingLayer._writeToStream(stream);
            return stream;
        }

        BlockingLayer& setBlockingTile(quint16 x, quint16 y, bool blocking);

    private:
        void _writeToStream(QDataStream&) const;
        void _loadFromStream(QDataStream&);

        quint16 m_width, m_height;

    };
}
