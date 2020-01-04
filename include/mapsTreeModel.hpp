#ifndef MAPTREEMODEL_H
#define MAPTREEMODEL_H

#include <QStandardItemModel>

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

class QDomNode;

namespace Misc {

//////////////////////////////////////////////////////////////////////////////
//  MapTreeModel class
//////////////////////////////////////////////////////////////////////////////

class MapTreeModel : public QStandardItemModel
{
public:
    MapTreeModel(const QDomNode& mapsNode);
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const override;

private:
    void setupModelData(const QDomNode& mapsNode, QStandardItem* parent);
};
} // namespace Misc

#endif // MAPTREEMODEL_H
