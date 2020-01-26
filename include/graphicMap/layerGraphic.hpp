#ifndef GRAPHICLAYER_H
#define GRAPHICLAYER_H

#include <QGraphicsItemGroup>
#include <memory>

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace LayerClipboard {
class Clipboard;
} // namespace LayerClipboard

namespace GraphicMap {

//////////////////////////////////////////////////////////////////////////////
//  GraphicLayer class
//////////////////////////////////////////////////////////////////////////////

class MapSceneLayer : public QObject
{
    Q_OBJECT
public:
    explicit MapSceneLayer(int zIndex);
    virtual std::shared_ptr<LayerClipboard::Clipboard> getClipboardRegion(const QRect& clip) = 0;

    QGraphicsItemGroup* graphicItems() { return m_items; }
    void clear();

public slots:
    void setVisibility(bool);
    virtual void setSelected() = 0;

protected:
    std::vector<QGraphicsItem*>& indexedItems() { return m_indexedItems; }

private:
    QGraphicsItemGroup* m_items = nullptr;
    std::vector<QGraphicsItem*> m_indexedItems;
};
} // namespace GraphicMap

#endif // GRAPHICLAYER_H
