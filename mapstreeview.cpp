#include <QAction>
#include <QDebug>

#include "dummy/map.h"
#include "dummy/project.h"
#include "mapstreeview.h"
#include "newmapdialog.h"


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
    NewMapDialog dlg;
    dlg.exec();

    Misc::MapTreeModel* mapModel = m_project->mapsModel();

    QModelIndex selectedIndex = currentIndex();
    QStandardItem* selectedParentMap = nullptr;

    if (selectedIndex.row() == -1) {
        selectedParentMap = mapModel->invisibleRootItem();
    } else {
        selectedParentMap =
            mapModel->itemFromIndex(selectedIndex);
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
        expand(selectedIndex);
    }
}

void MapsTreeView::_onPropertiesAction() {

}
