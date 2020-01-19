#include "mapsTree.hpp"

#include <QAction>
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
    connect(m_newMapDialog, SIGNAL(finished(int)), this, SLOT(createMap(int)));
    // connect edit dialog
    connect(m_editDialog, SIGNAL(finished(int)), this, SLOT(editMap(int)));
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

void MapsTreeView::createMap(int result)
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

void MapsTreeView::editMap(int result)
{
    if (result != QDialog::Accepted)
        return;

    // TODO changing the name has influence on its map<name;mapDoc> in
    // project... so it's harder, but should be possible

    std::string strChipset = m_editDialog->getChipset().toStdString();
    if (strChipset != m_editedMap->chipset()) {
        emit chipsetMapChanged(QString::fromStdString(
            (m_project->coreProject().projectPath() / "chipsets" / strChipset)
                .string()));
        m_editedMap->setChipset(strChipset);
    }
    m_editedMap->setMusic(m_editDialog->getMusic().toStdString());

    quint16 width  = m_editDialog->getWidth();
    quint16 height = m_editDialog->getHeight();

    if (width != m_editedMap->width() || height != m_editedMap->height()) {
        m_editedMap->resize(width, height);
    }
}

void MapsTreeView::showEditDlg()
{
    const QStandardItem* item =
        m_project->mapsModel()->itemFromIndex(m_selectedIndex);
    auto mapDocument = m_project->document(item->text());

    m_editedMap = mapDocument->m_map;

    m_editDialog->setup(*m_project, mapDocument);
    m_editDialog->open();
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
