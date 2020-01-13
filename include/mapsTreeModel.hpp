#ifndef MAPTREEMODEL_H
#define MAPTREEMODEL_H

#include <QStandardItemModel>

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

class QDomNode;

//////////////////////////////////////////////////////////////////////////////
//  MapTreeModel class
// a MapTreeModel is a wrapper around data to display in in MapsTreeView
//////////////////////////////////////////////////////////////////////////////

class MapsTreeModel : public QStandardItemModel
{
public:
    explicit MapsTreeModel(const QDomNode& mapsNode);
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const override;

private:
    void XmlMapToQItem(const QDomNode& mapsNode, QStandardItem* parent);
};

#endif // MAPTREEMODEL_H
