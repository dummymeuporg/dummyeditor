#include "mainWindow.hpp"

#include <filesystem>

#include <QCloseEvent>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QShortcut>

#include "definitions.hpp"
#include "drawingTool/blockingEraser.hpp"
#include "drawingTool/blockingPen.hpp"
#include "drawingTool/drawingSelection.hpp"
#include "editor/map.hpp"

#include "graphicMap/layerGraphicBlocking.hpp"
#include "graphicMap/layerGraphicVisible.hpp"
#include "graphicMap/mapGraphicsScene.hpp"

#include "chipsetGraphicsScene.hpp"
#include "mapDocument.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
    , m_chipsetScene(new ChipsetGraphicsScene())
    , m_mapScene(new GraphicMap::MapGraphicsScene())
{
    m_ui->setupUi(this);

    m_graphicTools.push_back(new DrawingTools::GraphicPen(*m_mapScene));
    m_graphicTools.push_back(new DrawingTools::GraphicRectangle(*m_mapScene));
    m_graphicTools.push_back(new DrawingTools::GraphicEraser(*m_mapScene));
    m_graphicTools.push_back(new DrawingTools::SelectionTool(*m_mapScene));

    m_blockingTools.push_back(new DrawingTools::BlockingPen(*m_mapScene));
    m_blockingTools.push_back(new DrawingTools::BlockingEraser(*m_mapScene));

    /*----------------------tab GENERAL---------------------------------- */

    // add a toolbar in the top of gridlayout
    QToolBar* tabGeneralToolBar = new QToolBar();
    tabGeneralToolBar->setStyleSheet("QToolBar{background-color: #ABABAB;}");

    // create a group action to regroup action layers
    QActionGroup* layersGroup = new QActionGroup(this);
    layersGroup->addAction("Working layer");
    layersGroup->addAction(m_ui->actionLow_layer_1);
    layersGroup->addAction(m_ui->actionLow_layer_2);
    layersGroup->addAction(m_ui->actionHigh_layer_1);
    layersGroup->addAction(m_ui->actionHigh_layer_2);
    layersGroup->addAction(m_ui->actionBlocking_layer);
    layersGroup->addAction(m_ui->actionEvents_layer);
    layersGroup->addAction(m_ui->actionQuick_go_admin);
    layersGroup->addAction(m_ui->actionStarting_point);
    layersGroup->addAction(m_ui->actionRespawn_point);
    tabGeneralToolBar->addActions(layersGroup->actions());

    tabGeneralToolBar->addSeparator();

    // create a group action to regroup action launch test
    QActionGroup* launchTestGroup = new QActionGroup(this);
    launchTestGroup->setExclusive(false);
    launchTestGroup->addAction("Launch test settings");
    launchTestGroup->addAction(m_ui->actionLaunch_test);
    launchTestGroup->addAction(m_ui->actionActivate_fullscreen);
    launchTestGroup->addAction(m_ui->actionActivate_music);
    launchTestGroup->addAction(m_ui->actionActivate_character_setting);
    tabGeneralToolBar->addActions(launchTestGroup->actions());

    m_ui->tabGeneral->layout()->setMenuBar(tabGeneralToolBar);
    initializeScenes();

    QObject::connect(m_ui->treeViewMaps, SIGNAL(chipsetMapChanged(QString)),
                     m_chipsetScene, SLOT(changeChipset(QString)));

    m_ui->graphicsViewChipset->scale(2.0, 2.0);
    m_ui->graphicsViewMap->scale(2.0, 2.0);

    QList<int> desktopSizeListWidth {width() / 5, (3 * width()) / 5};
    m_ui->splitter_2->setSizes(desktopSizeListWidth);

    QList<int> desktopSizeListHeight {(3 * height()) / 5, height() / 5};
    m_ui->splitter->setSizes(desktopSizeListHeight);

    /******************************************************
     * MainWindows items connection and shortcut setting  *
     ******************************************************/

    connect(m_ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    m_ui->actionQuit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    m_ui->actionQuit->setShortcutContext(Qt::ApplicationShortcut);

    m_ui->actionNew->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    m_ui->actionNew->setShortcutContext(Qt::ApplicationShortcut);

    m_ui->actionOpen->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    m_ui->actionOpen->setShortcutContext(Qt::ApplicationShortcut);

    m_ui->actionSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    m_ui->actionSave->setShortcutContext(Qt::ApplicationShortcut);

    m_ui->actionUndo->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    m_ui->actionUndo->setShortcutContext(Qt::ApplicationShortcut);

    m_ui->actionRedo->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));
    m_ui->actionRedo->setShortcutContext(Qt::ApplicationShortcut);

    m_ui->actionCut->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    m_ui->actionCut->setShortcutContext(Qt::WindowShortcut);

    m_ui->actionCopy->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    m_ui->actionCopy->setShortcutContext(Qt::WindowShortcut);

    m_ui->actionPaste->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    m_ui->actionPaste->setShortcutContext(Qt::WindowShortcut);
}

MainWindow::~MainWindow()
{
    if (m_currentProject != nullptr) {
        closeCurrentProject();
        m_currentProject.reset();
    }
    for (auto* tool : m_blockingTools) {
        delete tool;
    }
    for (auto* tool : m_graphicTools) {
        delete tool;
    }
    delete m_ui;
}

void MainWindow::visitGraphicLayer(GraphicMap::VisibleGraphicLayer& layer)
{
    // Publish visible/graphic related tools
    m_ui->widgetDrawingToolbox->onLayerSelected(m_mapScene, m_chipsetScene,
                                                layer, &m_graphicTools);
}

void MainWindow::visitGraphicLayer(GraphicMap::BlockingGraphicLayer& layer)
{
    // Publish blocking related tools
    m_ui->widgetDrawingToolbox->onLayerSelected(m_mapScene, m_chipsetScene,
                                                layer, &m_blockingTools);
}

void MainWindow::initializeScenes()
{
    m_ui->graphicsViewChipset->setScene(m_chipsetScene);
    m_ui->graphicsViewMap->setScene(m_mapScene);
}

void MainWindow::connectScenes()
{
    QObject::connect(m_ui->treeViewMaps, SIGNAL(chipsetMapChanged(QString)),
                     m_chipsetScene, SLOT(changeChipset(QString)));
}

void MainWindow::closeCurrentProject()
{
    // TODO clean currently loaded project
    delete m_chipsetScene;
    delete m_mapScene;
}

void MainWindow::loadProject(const QString& projectDirectory)
{
    connectScenes();

    m_currentProject = std::make_shared<Editor::Project>(
        std::filesystem::path(projectDirectory.toStdString()).string());

    m_ui->treeViewMaps->setModel(
        static_cast<QAbstractItemModel*>(m_currentProject->mapsModel()));

    m_ui->treeViewMaps->setProject(m_currentProject);

    // Enable the first layer drawing by default.
    m_ui->actionLow_layer_1->trigger();
}

void MainWindow::removeTools()
{
    qDebug() << "Remove tools";
    m_mapScene->unsetDrawingTool();
    m_chipsetScene->unsetPaletteTool();
    m_ui->widgetDrawingToolbox->clear();
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (nullptr != m_currentProject) {
        QMessageBox::StandardButton resBtn = QMessageBox::question(
            this, "DummyEditor", tr("Do you want to save before you quit ?\n"),
            QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
            QMessageBox::Cancel);

        switch (resBtn) {
        case QMessageBox::Yes:
            m_currentProject->saveProject();
            event->accept();
            break;
        case QMessageBox::No:
            event->accept();
            break;
        case QMessageBox::Cancel:
            event->ignore();
            break;
        default:
            break;
        }
    }
}

void MainWindow::on_actionNew_triggered()
{
    // Open a file dialog to select a folder
    QString projectDirectory = QFileDialog::getExistingDirectory(
        this, tr("Choose your project directory"));

    if (projectDirectory == "")
        return;

    if (nullptr != m_currentProject)
        closeCurrentProject();

    // Initialize a project into this directory
    Editor::Project::create(projectDirectory);

    loadProject(projectDirectory);
}

void MainWindow::on_actionOpen_triggered()
{
    QString projectDirectory = QFileDialog::getExistingDirectory(
        this, tr("Choose an existing project directory"));

    if (projectDirectory == "")
        return;

    if (nullptr != m_currentProject)
        closeCurrentProject();

    loadProject(projectDirectory);
}

void MainWindow::on_actionSave_triggered()
{
    if (m_currentProject != nullptr)
        m_currentProject->saveProject();
}

void MainWindow::on_treeViewMaps_doubleClicked(const QModelIndex& selectedIndex)
{
    const MapsTreeModel* mapModel = m_currentProject->mapsModel();

    QString mapName(mapModel->itemFromIndex(selectedIndex)->text());
    qDebug() << mapName;
    std::shared_ptr<Editor::Map> map(m_currentProject->document(mapName)->m_map);
    m_chipsetScene->setChipset((m_currentProject->coreProject().projectPath()
                                / "chipsets" / map->chipset())
                                   .string()
                                   .c_str());

    m_mapScene->setMapDocument(m_currentProject->document(mapName));

    for (const auto* layer : m_mapScene->graphicLayers()) {
        // XXX: connect the layers to the main window in order
        // to publish tools.
        QObject::connect(layer,
                         SIGNAL(layerSelected(GraphicMap::GraphicLayer*)), this,
                         SLOT(publishTools(GraphicMap::GraphicLayer*)));
    }

    m_ui->graphicsViewChipset->viewport()->update();
    m_ui->graphicsViewMap->setSceneRect(
        QRect(0, 0, map->width() * CELL_W, map->height() * CELL_H));

    auto* mapFloorsList = reinterpret_cast<MapFloorsList::FloorListWidget*>(
        m_ui->dockWidgetMapFloorsList->widget());

    mapFloorsList->setEditorMap(map);
    removeTools();
    m_ui->widgetDrawingToolbox->setInitialState();
}


void MainWindow::on_actionUndo_triggered()
{
    qDebug() << "Undo. Not implemented";
}

void MainWindow::on_actionRedo_triggered()
{
    qDebug() << "Redo. Not implemented";
}

void MainWindow::on_actionCut_triggered()
{
    // Cut is only active for SelectionTool
    auto* activeTool =
        dynamic_cast<DrawingTools::SelectionTool*>(m_mapScene->drawingTool());
    if (activeTool != nullptr) {
        activeTool->doCut();
    }
}

void MainWindow::on_actionCopy_triggered()
{
    // Copy is only active for SelectionTool
    auto* activeTool =
        dynamic_cast<DrawingTools::SelectionTool*>(m_mapScene->drawingTool());
    if (activeTool != nullptr) {
        activeTool->doCopy();
    }
}

void MainWindow::on_actionPaste_triggered()
{
    // Paste is only active for SelectionTool
    auto* activeTool =
        dynamic_cast<DrawingTools::SelectionTool*>(m_mapScene->drawingTool());
    if (activeTool != nullptr) {
        activeTool->doPaste();
    }
}

void MainWindow::publishTools(GraphicMap::GraphicLayer* layer)
{
    qDebug() << "Publish tools!";
    // XXX: if we are publishing (new tools), make the map scene
    // unselect its previous tool (if any).
    // ...
    // Not sure this is a fancy way to do so, though.
    // m_mapScene->unsetDrawingTool();
    // m_chipsetScene->unsetPaletteTool();

    /*
  std::vector<DrawingTool::DrawingTool*>&& tools(layer->drawingTools());
  auto toolbox = ui->widgetDrawingToolbox;
  toolbox->reset(m_mapScene, m_chipsetScene, tools);
  */

    layer->accept(*this);
}
