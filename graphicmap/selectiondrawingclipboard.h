#pragma once

#include <QRect>
#include <QVector>

namespace GraphicMap {

    class SelectionDrawingTool;

    class SelectionDrawingClipboard
    {
    public:
        SelectionDrawingClipboard(SelectionDrawingTool&);

        inline const QRect& selectionClipboard() const {
            return m_selectionClipboard;
        }

        inline const QVector<std::tuple<qint16, qint16>>&
        firstLayerClipboard() const {
            return m_firstLayerClipboard;
        }

        inline const QVector<std::tuple<qint16, qint16>>&
        secondLayerClipboard() const {
            return m_secondLayerClipboard;
        }

        inline const QVector<std::tuple<qint16, qint16>>&
        thirdLayerClipboard() const {
            return m_thirdLayerClipboard;
        }

        const QVector<bool>& blockingLayerClipboard() const
        {
            return m_blockingLayerClipboard;
        }

    private:
        SelectionDrawingTool& m_selectionDrawingTool;
        QRect m_selectionClipboard;
        QVector<std::tuple<qint16, qint16>>
            m_firstLayerClipboard,
            m_secondLayerClipboard,
            m_thirdLayerClipboard;
        QVector<bool> m_blockingLayerClipboard;
    };
}
