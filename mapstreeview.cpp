#include <QAction>
#include <QDebug>
#include <QTreeWidgetItem>

#include "dummy/map.h"
#include "dummy/project.h"
#include "mapstreeview.h"
#include "mapeditdialog.h"


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
        Dummy::Map map(dlg.getWidth(), dlg.getHeight());
        map.setChipset(dlg.getChipset()).setMusic(dlg.getMusic());
        map.saveToFile(m_project->fullpath() +
                       "/maps/" + mapName + ".map");

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
    std::shared_ptr<Dummy::Map> map(m_project->document(item->text()).map());
    MapEditDialog dlg(m_project, map);
    dlg.exec();
    if (dlg.result() == QDialog::Accepted) {
        map->setChipset(dlg.getChipset()).setMusic(dlg.getMusic());
        map->saveToFile(m_project->fullpath() +
                        "/maps/" + map->name() + ".map");
    }

}
