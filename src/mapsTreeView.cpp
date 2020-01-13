#include "mapsTreeView.hpp"

#include <QAction>
#include <QDebug>
#include <QTreeWidgetItem>

#include "editor/layerBlocking.hpp"
#include "editor/layerEvents.hpp"
#include "editor/layerGraphic.hpp"
#include "editor/map.hpp"
#include "mapDocument.hpp"
#include "mapEditDialog.hpp"


MapsTreeView::MapsTreeView(QWidget* parent)
    : QTreeView(parent)
    , m_mapMenu(new QMenu(this))
    , m_newMapAction(new QAction(tr("Add new map"), this))
    , m_propertiesAction(new QAction(tr("Properties"), this))
{
    m_mapMenu->addAction(m_newMapAction);
    m_mapMenu->addAction(m_propertiesAction);
    m_mapMenu->setEnabled(false);

    connect(m_newMapAction, SIGNAL(triggered()), this, SLOT(onNewMapAction()));
    connect(m_propertiesAction, SIGNAL(triggered()), this,
            SLOT(onPropertiesAction()));

    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
            SLOT(showContextMenu(const QPoint&)));
}

void MapsTreeView::setProject(std::shared_ptr<Editor::Project> project)
{
    m_project = project;

    // Disable right-click menu if no project is loaded
    bool projectNotNull = (project != nullptr);
    m_mapMenu->setEnabled(projectNotNull);
}

void MapsTreeView::showContextMenu(const QPoint& point)
{
    // Find on which item we clicked
    m_selectedModelIndex = indexAt(point);

    // Activate "Properties" Action if we clicked on an item
    bool clickedOnItem = m_selectedModelIndex.isValid();
    m_propertiesAction->setEnabled(clickedOnItem);

    // And finally show the contextual menu
    m_mapMenu->exec(viewport()->mapToGlobal(point));
}

void MapsTreeView::onNewMapAction()
{
    // TODO move that "logical" part to a logical class instead of here
    if (m_project == nullptr)
        return; // not supposed to happen

    MapEditDialog dlg;
    dlg.setup(*m_project);

    // TODO use open() + connect to finished() instead of exec()
    if (dlg.exec() != QDialog::Accepted)
        return;

    const MapsTreeModel* mapModel = m_project->mapsModel();
    if (nullptr == mapModel) {
        return;
    }

    QStandardItem* selectedParentMap = nullptr;

    if (! m_selectedModelIndex.isValid()) {
        selectedParentMap = mapModel->invisibleRootItem();
    } else {
        selectedParentMap = mapModel->itemFromIndex(m_selectedModelIndex);
    }

    QString mapName = dlg.getMapName();
    // XXX: Create (or edit) map

    auto map = std::make_shared<Editor::Map>(m_project->coreProject(),
                                             mapName.toStdString());
    map->setChipset(dlg.getChipset().toStdString());
    map->setMusic(dlg.getMusic().toStdString());
    map->reset(dlg.getWidth(), dlg.getHeight());

    auto mapDocument = std::make_shared<MapDocument>(*m_project, mapName, map);

    // XXX: For now, create one floor with four layers.
    // The layers will have for positions :
    // -1 (the lowest one)
    // 0 (the one juste below the character)
    // 1 (the one juste above the character)
    // 2 (another one above)
    Dummy::Local::Floor floor(*map);
    floor.addGraphicLayer(
        -1, Dummy::Core::GraphicLayer(dlg.getWidth(), dlg.getHeight()));
    floor.addGraphicLayer(
        0, Dummy::Core::GraphicLayer(dlg.getWidth(), dlg.getHeight()));
    floor.addGraphicLayer(
        1, Dummy::Core::GraphicLayer(dlg.getWidth(), dlg.getHeight()));
    floor.addGraphicLayer(
        2, Dummy::Core::GraphicLayer(dlg.getWidth(), dlg.getHeight()));

    map->addFloor(std::make_unique<Editor::Floor>(floor));
    map->resize(dlg.getWidth(), dlg.getHeight());

    map->save();
    // Add the new map into the tree.
    QList<QStandardItem*> mapRow{new QStandardItem(mapName)};
    selectedParentMap->appendRow(mapRow);
    expand(m_selectedModelIndex);
}

void MapsTreeView::onPropertiesAction()
{
    // TODO move that "logical" part to a logical class instead of here
    QStandardItem* item =
        m_project->mapsModel()->itemFromIndex(m_selectedModelIndex);
    qDebug() << item->text();
    std::shared_ptr<MapDocument> mapDocument(m_project->document(item->text()));
    auto map(mapDocument->map);
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
