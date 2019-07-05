#include <filesystem>

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMessageBox>

#include "editor/map.hpp"
#include "editor/project.hpp"

#include "misc/map_tree_model.hpp"

#include "chipsetgraphicsscene.hpp"
#include "graphicmap/mapgraphicsscene.hpp"
#include "mainwindow.hpp"
#include "mapeditdialog.hpp"
#include "widget/map_levels_list/widget.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_currentProject(nullptr),
    m_chipsetScene(nullptr),
    m_mapScene(nullptr)
{
    ui->setupUi(this);


    /*----------------------tab GENERAL---------------------------------- */

    //add a toolbar in the top of gridlayout
    QToolBar *tabGeneralToolBar = new QToolBar();
    tabGeneralToolBar->setStyleSheet("QToolBar{background-color: #ABABAB;}");

    //create a group action to regroup action tools
    QActionGroup *toolsGroup = new QActionGroup(this);
    toolsGroup->addAction("Working tool");
    toolsGroup->addAction(ui->actionSelection);
    //toolsGroup->addAction(ui->actionPen);
    toolsGroup->addAction(ui->actionRectangle);
    toolsGroup->addAction(ui->actionPath);
    tabGeneralToolBar->addActions(toolsGroup->actions());

    tabGeneralToolBar->addSeparator();

    //create a group action to regroup action layers
    QActionGroup *layersGroup = new QActionGroup(this);
    layersGroup->addAction("Working layer");
    layersGroup->addAction(ui->actionLow_layer_1);
    layersGroup->addAction(ui->actionLow_layer_2);
    layersGroup->addAction(ui->actionHigh_layer_1);
    layersGroup->addAction(ui->actionHigh_layer_2);
    layersGroup->addAction(ui->actionBlocking_layer);
    layersGroup->addAction(ui->actionEvents_layer);
    layersGroup->addAction(ui->actionQuick_go_admin);
    layersGroup->addAction(ui->actionStarting_point);
    layersGroup->addAction(ui->actionRespawn_point);
    tabGeneralToolBar->addActions(layersGroup->actions());

    tabGeneralToolBar->addSeparator();

    //create a group action to regroup action launch test
    QActionGroup *launchTestGroup = new QActionGroup(this);
    launchTestGroup->setExclusive(false);
    launchTestGroup->addAction("Launch test settings");
    launchTestGroup->addAction(ui->actionLaunch_test);
    launchTestGroup->addAction(ui->actionActivate_fullscreen);
    launchTestGroup->addAction(ui->actionActivate_music);
    launchTestGroup->addAction(ui->actionActivate_character_setting);
    tabGeneralToolBar->addActions(launchTestGroup->actions());


    ui->tabGeneral->layout()->setMenuBar(tabGeneralToolBar);
    _initializeScenes();

    QObject::connect(ui->treeViewMaps, SIGNAL(chipsetMapChanged(QString)),
                     m_chipsetScene, SLOT(changeChipset(QString)));
    QObject::connect(m_chipsetScene, SIGNAL(selectionChanged(QRect)),
                     m_mapScene, SLOT(changeSelection(QRect)));

    ui->graphicsViewChipset->scale(2.0, 2.0);
    ui->graphicsViewMap->scale(2.0, 2.0);

}

void MainWindow::_initializeScenes()
{
    m_chipsetScene = new ChipsetGraphicsScene();

    ui->graphicsViewChipset->setScene(m_chipsetScene);

    m_mapScene = new GraphicMap::MapGraphicsScene();

    ui->graphicsViewMap->setScene(m_mapScene);
}

void MainWindow::_connectScenes()
{
    QObject::connect(ui->treeViewMaps, SIGNAL(chipsetMapChanged(QString)),
                     m_chipsetScene, SLOT(changeChipset(QString)));
    QObject::connect(m_chipsetScene, SIGNAL(selectionChanged(QRect)),
                     m_mapScene, SLOT(changeSelection(QRect)));

    /*
    QObject::connect(ui->actionPen, SIGNAL(triggered(bool)),
                     m_mapScene, SLOT(setPenTool()));
    QObject::connect(ui->actionRectangle,
                     SIGNAL(triggered(bool)),
                     m_mapScene,
                     SLOT(setRectangleTool()));
    QObject::connect(ui->actionSelection,
                     SIGNAL(triggered(bool)),
                     m_mapScene,
                     SLOT(setSelectionTool()));
    */

}

void MainWindow::_closeCurrentProject()
{
    QObject::disconnect(ui->treeViewMaps, SIGNAL(chipsetMapChanged(QString)),
                        m_chipsetScene, SLOT(changeChipset(QString)));
    QObject::disconnect(m_chipsetScene, SIGNAL(selectionChanged(QRect)),
                        m_mapScene, SLOT(changeSelection(QRect)));

    QObject::disconnect(ui->actionLow_layer_1, SIGNAL(triggered(bool)),
                        m_mapScene, SLOT(showFirstLayer()));
    QObject::disconnect(ui->actionLow_layer_2, SIGNAL(triggered(bool)),
                        m_mapScene, SLOT(showSecondLayer()));
    QObject::disconnect(ui->actionHigh_layer_1, SIGNAL(triggered(bool)),
                        m_mapScene, SLOT(showThirdLayer()));
    QObject::disconnect(ui->actionHigh_layer_2, SIGNAL(triggered(bool)),
                        m_mapScene, SLOT(showFourthLayer()));
    QObject::disconnect(ui->actionBlocking_layer, SIGNAL(triggered(bool)),
                        m_mapScene, SLOT(showBlockingLayer()));
    QObject::disconnect(ui->actionStarting_point, SIGNAL(triggered(bool)),
                        m_mapScene, SLOT(showStartingPointLayer()));

    /*
    QObject::disconnect(ui->actionPen, SIGNAL(triggered(bool)),
                        m_mapScene, SLOT(setPenTool()));
    QObject::disconnect(ui->actionPen, SIGNAL(trigerred(bool)),
                        m_mapScene, SLOT(setPenTool()));

    QObject::disconnect(ui->actionSelection,
                        SIGNAL(triggered(bool)),
                        m_mapScene,
                        SLOT(setSelectionTool()));
    */
    delete m_chipsetScene;
    delete m_mapScene;
}


MainWindow::~MainWindow()
{
    if (m_currentProject != nullptr) {
        m_currentProject.reset();
    }
    delete ui;
}

void MainWindow::newProject() {
    // Open a file dialog to select a folder
    QString projectDirectory =
        QFileDialog::getExistingDirectory(this,
                                          tr("Choose your project directory"));

    if (projectDirectory == "") {
        return;
    }

    // Initialize a project into this directory
    _initializeProject(projectDirectory);

    if (nullptr != m_currentProject) {
        _closeCurrentProject();
    }

    _loadProject(projectDirectory);

}

void MainWindow::openProject() {

    if (nullptr != m_currentProject) {
        _closeCurrentProject();
    }

    QString projectDirectory =
        QFileDialog::getExistingDirectory(
            this, tr("Choose an existing project directory"));

    if (projectDirectory == "") {
        return;
    }

    _loadProject(projectDirectory);

}

void MainWindow::_loadProject(const QString& projectDirectory) {

    _connectScenes();

    m_currentProject = std::make_shared<Editor::Project>(
        std::filesystem::path(projectDirectory.toStdString()).string()
    );

    ui->treeViewMaps->setModel(
        static_cast<QAbstractItemModel*>(m_currentProject->mapsModel())
    );

    ui->treeViewMaps->setProject(m_currentProject);

    // Enable the first layer drawing by default.
    ui->actionLow_layer_1->trigger();
}

void MainWindow::saveProject() {
    if (nullptr != m_currentProject) {
        m_currentProject->saveProjectFile();
        qDebug() << m_currentProject->openedMaps().count();
        if (m_currentProject->openedMaps().count() > 0) {
            QMap<QString, Misc::MapDocument>::iterator i;

            for(auto e : m_currentProject->openedMaps().keys()) {
                qDebug() << e;
                m_currentProject->document(e)->save();
            }
        }
    }
}


void MainWindow::_initializeProject(const QString& projectDirectory) {
    Editor::Project::create(projectDirectory);
}

void MainWindow::selectCurrentMap(QModelIndex selectedIndex) {
    Misc::MapTreeModel* mapModel = m_currentProject->mapsModel();

    QString mapName(mapModel->itemFromIndex(selectedIndex)->text());
    qDebug() << mapName;
    std::shared_ptr<Editor::Map> map(
        m_currentProject->document(mapName)->map());
    m_chipsetScene->setChipset(
        (m_currentProject->coreProject().projectPath()
         / "chipsets" / map->chipset()).string().c_str()
    );

    m_mapScene->setMapDocument(m_currentProject->document(mapName));

    for (const auto& layer: m_mapScene->graphicLayers()) {
    }

    ui->graphicsViewChipset->viewport()->update();
    ui->graphicsViewMap->setSceneRect(QRect(0,
                                            0,
                                            map->width()*16,
                                            map->height()*16));

    reinterpret_cast<Widget::MapLevelsList::Widget*>(
        ui->dockWidgetMapLevelsList->widget()
    )->setEditorMap(map);

    // Connect each graphic layer to this window's slot
}

void MainWindow::onCancel()
{
    qDebug() << "Cancel.";
}

void MainWindow::onCut()
{
    qDebug() << "Cut.";
    QKeyEvent* keyEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_X,
                                        Qt::ControlModifier);
    QCoreApplication::postEvent(m_mapScene, keyEvent);
}

void MainWindow::onCopy()
{
    qDebug() << "Copy.";
    QKeyEvent* keyEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_C,
                                        Qt::ControlModifier);
    QCoreApplication::postEvent(m_mapScene, keyEvent);
}

void MainWindow::onPaste()
{
    qDebug() << "Paste.";
    QKeyEvent* keyEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_V,
                                        Qt::ControlModifier);
    QCoreApplication::postEvent(m_mapScene, keyEvent);
}
