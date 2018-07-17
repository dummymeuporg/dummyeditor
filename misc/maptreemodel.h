#ifndef _MISC_MAPTREEMODEL_H
#define _MISC_MAPTREEMODEL_H

#include <QStandardItemModel>
#include <QVariant>

class QStandardItem;
class QDomNode;

namespace Misc {
    class MapTreeModel : public QStandardItemModel
    {
    public:
        MapTreeModel(const QDomNode& mapsNode);
        QVariant headerData(int section,
                           Qt::Orientation orientation,
                           int role) const override;

    private:
        void setupModelData(const QDomNode& mapsNode, QStandardItem* parent);
    };
}

#endif // MAPTREEMODEL_H
