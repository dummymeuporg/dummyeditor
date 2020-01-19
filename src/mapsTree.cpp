#include "mapsTree.hpp"

#include <QAction>
#include <QDebug>
#include <QDomNode>
#include <QTreeWidgetItem>

#include "editor/map.hpp"
#include "editor/project.hpp"
#include "mapDocument.hpp"
#include "mapEditDialog.hpp"

MapsTreeView::MapsTreeView(QWidget* parent)
    : QTreeView(parent)
    , m_mapMenu(new QMenu(this))
    , m_newMapAction(new QAction(tr("Add new map"), this))
    , m_editAction(new QAction(tr("Properties"), this))
    , m_newMapDialog(new MapEditDialog(this))
    , m_editDialog(new MapEditDialog(this))
{
    // add actions to menu
    m_mapMenu->addAction(m_newMapAction);
    m_mapMenu->addAction(m_editAction);
    // connect actions
    connect(m_newMapAction, SIGNAL(triggered()), this, SLOT(showNewMapDlg()));
    connect(m_editAction, SIGNAL(triggered()), this, SLOT(showEditDlg()));
    // connect menu pop-up
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this,
            SLOT(showContextMenu(const QPoint&)));
    m_mapMenu->setEnabled(false);

    // connect new map dialog
    connect(m_newMapDialog, SIGNAL(finished(int)), this,
            SLOT(createNewMap(int)));
    // connect edit dialog
    // connect(m_editDialog, SIGNAL(finished(int)), this,
    // SLOT(dialogIsFinished(int)));
}

void MapsTreeView::setProject(std::shared_ptr<Editor::Project> project)
{
    m_project = project;

    if (project != nullptr) {
        setModel(project->mapsModel());
        m_mapMenu->setEnabled(true);
    } else {
        setModel(nullptr);
        m_mapMenu->setEnabled(false);
    }
}

void MapsTreeView::clear()
{
    setProject(nullptr);
}

void MapsTreeView::showContextMenu(const QPoint& point)
{
    m_selectedIndex = indexAt(point);

    // Activate "Properties" Action if we clicked on an item
    bool clickedOnItem = m_selectedIndex.isValid();
    m_editAction->setEnabled(clickedOnItem);

    // And finally show the contextual menu
    m_mapMenu->exec(viewport()->mapToGlobal(point));
}

void MapsTreeView::showNewMapDlg()
{
    if (m_project == nullptr)
        return; // not supposed to happen

    m_newMapDialog->setup(*m_project);
    m_newMapDialog->open();
}

void MapsTreeView::addMapAtRoot()
{
    m_selectedIndex = QModelIndex();
    showNewMapDlg();
}

void MapsTreeView::createNewMap(int result)
{
    if (result != QDialog::Accepted)
        return;

    QStandardItemModel* mapsModel = qobject_cast<QStandardItemModel*>(model());
    if (mapsModel == nullptr)
        return;

    QStandardItem* selectedParentMap = mapsModel->invisibleRootItem();
    if (m_selectedIndex.isValid()) {
        selectedParentMap = mapsModel->itemFromIndex(m_selectedIndex);
    }

    if (m_project == nullptr || selectedParentMap == nullptr)
        return;

    Editor::tMapInfo mapInfo;
    mapInfo.m_mapName     = m_newMapDialog->getMapName().toStdString();
    mapInfo.m_chispetPath = m_newMapDialog->getChipset().toStdString();
    mapInfo.m_musicPath   = m_newMapDialog->getMusic().toStdString();
    mapInfo.m_width       = m_newMapDialog->getWidth();
    mapInfo.m_height      = m_newMapDialog->getHeight();

    m_project->createMap(mapInfo, *selectedParentMap);

    expand(m_selectedIndex);
}

void MapsTreeView::showEditDlg()
{
    // TODO move that "logical" part to a logical class instead of here
    const QStandardItem* item =
        m_project->mapsModel()->itemFromIndex(m_selectedIndex);

    std::shared_ptr<MapDocument> mapDocument(m_project->document(item->text()));
    auto map(mapDocument->m_map);
    // XXX fix this:

    MapEditDialog dlg;
    dlg.setup(*m_project, mapDocument);

    dlg.exec();
    if (dlg.result() == QDialog::Accepted) {
        QString dlgChipset = dlg.getChipset();
        if (dlgChipset.toStdString() != map->chipset()) {
            emit chipsetMapChanged(
                QString((m_project->coreProject().projectPath() / "chipsets"
                         / dlgChipset.toStdString())
                            .string()
                            .c_str()));
        }
        map->setChipset(dlg.getChipset().toStdString());
        map->setMusic(dlg.getMusic().toStdString());

        quint16 width  = dlg.getWidth();
        quint16 height = dlg.getHeight();

        if (width != map->width() || height != map->height()) {
            qDebug() << "Resize to " << width << ", " << height;
            map->resize(width, height);
        }

        // map->save();
    }
}

///////////////////////////////////////////////////////////////////////////////


MapsTreeModel::MapsTreeModel(const QDomNode& mapsNode)
{
    XmlMapToQItem(mapsNode, invisibleRootItem());
}

void MapsTreeModel::XmlMapToQItem(const QDomNode& node, QStandardItem* parent)
{
    const auto& children = node.childNodes();
    int nbChildren       = children.count();

    for (int i = 0; i < nbChildren; ++i) {
        const auto& n = children.at(i);

        if (n.nodeName() == "map") {
            QString mapName = n.attributes().namedItem("name").nodeValue();
            QStandardItem* mapItem = new QStandardItem(mapName);
            parent->appendRow(mapItem);

            XmlMapToQItem(n, mapItem);
        }
    }
}

QVariant MapsTreeModel::headerData(int section, Qt::Orientation orientation,
                                   int role) const
{
    if (role == Qt::DisplayRole          //
        && orientation == Qt::Horizontal //
        && section == 0)
        return QString("Maps");

    return QVariant();
}
