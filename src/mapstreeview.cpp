#include <QAction>
#include <QDebug>
#include <QTreeWidgetItem>

#include "editor/blocking_layer.hpp"
#include "editor/graphic_layer.hpp"
#include "editor/map.hpp"
#include "editor/floor.hpp"
#include "editor/project.hpp"

#include "mapstreeview.hpp"
#include "mapeditdialog.hpp"


MapsTreeView::MapsTreeView(QWidget* parent) : QTreeView(parent),
    m_project(nullptr),
    m_newMapAction(nullptr),
    m_propertiesAction(nullptr)
{

}

void MapsTreeView::_enableActions() {
    qDebug() << "Enable actions";


    m_newMapAction = new QAction(tr("Add new map"));
    m_propertiesAction = new QAction(tr("Properties"));

    m_mapMenu = new QMenu();
    m_mapMenu->addAction(m_newMapAction);
    m_mapMenu->addAction(m_propertiesAction);

    addAction(m_newMapAction);
    addAction(m_propertiesAction);
    QObject::connect(m_newMapAction,
                     SIGNAL(triggered()),
                     this,
                     SLOT(_onNewMapAction()));
    QObject::connect(m_propertiesAction,
                     SIGNAL(triggered()),
                     this,
                     SLOT(_onPropertiesAction()));
    connect(this,
            SIGNAL(customContextMenuRequested(const QPoint&)),
            SLOT(_showContextMenu(const QPoint&)));
}

void MapsTreeView::_showContextMenu(const QPoint& point) {

    m_selectedModelIndex = indexAt(point);

    if (m_selectedModelIndex.isValid()) {
        m_propertiesAction->setEnabled(true);
    } else {
        m_propertiesAction->setEnabled(false);
    }

    m_mapMenu->exec(viewport()->mapToGlobal(point));
}

void MapsTreeView::_disableActions() {
    removeAction(m_newMapAction);
    QObject::disconnect(m_newMapAction, SIGNAL(triggered()), this,
                        SLOT(_onNewMapAction()));
    QObject::disconnect(m_propertiesAction, SIGNAL(trigerred()), this,
                        SLOT(_onPropertiesAction()));
    delete m_newMapAction;
    delete m_propertiesAction;
}

void MapsTreeView::_onNewMapAction() {
    MapEditDialog dlg(m_project);
    dlg.exec();

    Misc::MapTreeModel* mapModel = m_project->mapsModel();

    QStandardItem* selectedParentMap = nullptr;

    if (!m_selectedModelIndex.isValid()) {
        selectedParentMap = mapModel->invisibleRootItem();
        qDebug() << "-1";
    } else {
        selectedParentMap =
            mapModel->itemFromIndex(m_selectedModelIndex);
        qDebug() << "parent";
    }

    qDebug() << selectedParentMap;

    if(dlg.result() == QDialog::Accepted) {
        QString mapName = dlg.getMapName();
        // XXX: Create (or edit) map

        auto map = std::make_shared<Editor::Map>(
            m_project->coreProject(), mapName.toStdString()
        );
        map->setChipset(dlg.getChipset().toStdString());
        map->setMusic(dlg.getMusic().toStdString());
        map->reset(dlg.getWidth(), dlg.getHeight());

        auto mapDocument = std::make_shared<Misc::MapDocument>(
            *m_project, mapName, map
        );

        // XXX: For now, create one floor with four layers.
        // The layers will have for positions :
        // -1 (the lowest one)
        // 0 (the one juste below the character)
        // 1 (the one juste above the character)
        // 2 (another one above)
        Dummy::Local::Floor floor(*map);
        floor.addGraphicLayer(
            -1,
            Dummy::Core::GraphicLayer(dlg.getWidth(), dlg.getHeight())
        );
        floor.addGraphicLayer(
            0,
            Dummy::Core::GraphicLayer(dlg.getWidth(), dlg.getHeight())
        );
        floor.addGraphicLayer(
            1,
            Dummy::Core::GraphicLayer(dlg.getWidth(), dlg.getHeight())
        );
        floor.addGraphicLayer(
            2,
            Dummy::Core::GraphicLayer(dlg.getWidth(), dlg.getHeight())
        );

        map->addFloor(std::make_unique<Editor::Floor>(floor));
        map->resize(dlg.getWidth(), dlg.getHeight());

        map->save();
        // Add the new map into the tree.
        QList<QStandardItem*> mapRow { new QStandardItem(mapName) };
        selectedParentMap->appendRow(mapRow);
        expand(m_selectedModelIndex);
    }
}

void MapsTreeView::_onPropertiesAction() {
    QStandardItem* item = m_project
            ->mapsModel()
            ->itemFromIndex(m_selectedModelIndex);
    qDebug() << item->text();
    std::shared_ptr<Misc::MapDocument> mapDocument(
        m_project->document(item->text())
    );
    auto map(mapDocument->map());
    //XXX fix this:

    MapEditDialog dlg(m_project, mapDocument);
    dlg.exec();
    if (dlg.result() == QDialog::Accepted) {
        QString dlgChipset = dlg.getChipset();
        if (dlgChipset.toStdString() != map->chipset()) {
            emit chipsetMapChanged(
                QString((m_project->coreProject().projectPath()
                / "chipsets"
                / dlgChipset.toStdString()).string().c_str())
            );
        }
        map->setChipset(dlg.getChipset().toStdString());
        map->setMusic(dlg.getMusic().toStdString());

        quint16 width = dlg.getWidth();
        quint16 height = dlg.getHeight();

        if (width != map->width() || height != map->height()) {
            qDebug() << "Resize to " << width << ", " << height;
            map->resize(width, height);
        }

        //map->save();
    }
}
