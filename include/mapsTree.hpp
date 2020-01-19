#ifndef MAPSTREE_H
#define MAPSTREE_H

#include <exception>
#include <memory>

#include <QMenu>
#include <QStandardItem>
#include <QTreeView>

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Dummy {
class Project;
}
namespace Editor {
class Project;
}
class QDomNode;
class MapEditDialog;

//////////////////////////////////////////////////////////////////////////////
//  MapsTreeView class
// a MapsTreeView represents a visual list of maps.
// It contains only the graphical representation and interactions. Data are
// kept in MapsTreeModel.
//////////////////////////////////////////////////////////////////////////////

class MapsTreeView : public QTreeView
{
    Q_OBJECT

public:
    explicit MapsTreeView(QWidget* parent = nullptr);

    void setProject(std::shared_ptr<Editor::Project> project);
    void clear();

public slots:
    void showNewMapDlg();
    void showEditDlg();
    void showContextMenu(const QPoint&);

    void addMapAtRoot();
    void createNewMap(int dlgButton);

signals:
    void chipsetMapChanged(QString);

private:
    std::shared_ptr<Editor::Project> m_project;
    QMenu* m_mapMenu              = nullptr;
    QAction* m_newMapAction       = nullptr;
    QAction* m_editAction         = nullptr;
    MapEditDialog* m_newMapDialog = nullptr;
    MapEditDialog* m_editDialog   = nullptr;
    QModelIndex m_selectedIndex;
};

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

#endif // MAPSTREEVIEW_H
