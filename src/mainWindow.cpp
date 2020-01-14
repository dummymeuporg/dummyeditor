#include "mainWindow.hpp"

#include <filesystem>

#include <QCloseEvent>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

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

    // create a group action to regroup action tools
    QActionGroup* toolsGroup = new QActionGroup(this);
    toolsGroup->addAction("Working tool");
    // toolsGroup->addAction(ui->actionSelection);
    // toolsGroup->addAction(ui->actionPen);
    // toolsGroup->addAction(ui->actionRectangle);
    // toolsGroup->addAction(ui->actionPath);
    tabGeneralToolBar->addActions(toolsGroup->actions());

    tabGeneralToolBar->addSeparator();

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
    /*
QObject::connect(m_chipsetScene, SIGNAL(selectionChanged(QRect)),
                 m_mapScene, SLOT(changeSelection(QRect)));
*/

    m_ui->graphicsViewChipset->scale(2.0, 2.0);
    m_ui->graphicsViewMap->scale(2.0, 2.0);

    QList<int> desktopSizeListWidth {width() / 5, 3 * width() / 5};
    m_ui->splitter_2->setSizes(desktopSizeListWidth);

    QList<int> desktopSizeListHeight {3 * height() / 5, height() / 5};
    m_ui->splitter->setSizes(desktopSizeListHeight);
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
    /*
QObject::connect(m_chipsetScene, SIGNAL(selectionChanged(QRect)),
                 m_mapScene, SLOT(changeSelection(QRect)));
*/

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

void MainWindow::closeCurrentProject()
{
    // TODO clean currently loaded project
    delete m_chipsetScene;
    delete m_mapScene;
}

MainWindow::~MainWindow()
{
    if (m_currentProject != nullptr) {
        closeCurrentProject();
        m_currentProject.reset();
    }
    for (auto tool : m_blockingTools) { delete tool; }
    for (auto tool : m_graphicTools) { delete tool; }
    delete m_ui;
}

void MainWindow::newProject()
{
    // Open a file dialog to select a folder
    QString projectDirectory = QFileDialog::getExistingDirectory(
        this, tr("Choose your project directory"));

    if (projectDirectory == "") {
        return;
    }

    if (nullptr != m_currentProject) {
        closeCurrentProject();
    }

    // Initialize a project into this directory
    Editor::Project::create(projectDirectory);

    loadProject(projectDirectory);
}

void MainWindow::openProject()
{
    if (nullptr != m_currentProject) {
        closeCurrentProject();
    }

    QString projectDirectory = QFileDialog::getExistingDirectory(
        this, tr("Choose an existing project directory"));

    if (projectDirectory == "") {
        return;
    }

    loadProject(projectDirectory);
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

void MainWindow::saveProject()
{
    if (nullptr == m_currentProject) {
        return;
    }

    m_currentProject->saveProjectFile();

    if (m_currentProject->openedMaps().count() <= 0) {
        return;
    }

    for (auto e : m_currentProject->openedMaps().keys()) {
        m_currentProject->document(e)->map->save();
    }
}

void MainWindow::selectCurrentMap(QModelIndex selectedIndex)
{
    const MapsTreeModel* mapModel = m_currentProject->mapsModel();

    QString mapName(mapModel->itemFromIndex(selectedIndex)->text());
    qDebug() << mapName;
    std::shared_ptr<Editor::Map> map(m_currentProject->document(mapName)->map);
    m_chipsetScene->setChipset((m_currentProject->coreProject().projectPath()
                                / "chipsets" / map->chipset())
                                   .string()
                                   .c_str());

    m_mapScene->setMapDocument(m_currentProject->document(mapName));

    for (const auto& layer : m_mapScene->graphicLayers()) {
        // XXX: connect the layers to the main window in order
        // to publish tools.
        QObject::connect(layer,
                         SIGNAL(layerSelected(GraphicMap::GraphicLayer*)), this,
                         SLOT(publishTools(GraphicMap::GraphicLayer*)));
    }

    m_ui->graphicsViewChipset->viewport()->update();
    m_ui->graphicsViewMap->setSceneRect(
        QRect(0, 0, map->width() * 16, map->height() * 16));

    auto mapFloorsList = reinterpret_cast<MapFloorsList::FloorListWidget*>(
        m_ui->dockWidgetMapFloorsList->widget());

    mapFloorsList->setEditorMap(map);
    removeTools();
    m_ui->widgetDrawingToolbox->setInitialState();
}

void MainWindow::onCancel()
{
    qDebug() << "Cancel.";
}

void MainWindow::onCut()
{
    qDebug() << "Cut.";
    // TODO it's not the best way to manage event.
    // Shortcut are good to be kept customisable. If we do so in the future,
    // we'll need to update all those methods. Future refacto : expose the event
    // to call and call it directly. And from the other way, use QShortcut (we
    // might need to set shortcutContext) instead of keypressevent
    QKeyEvent* keyEvent =
        new QKeyEvent(QEvent::KeyPress, Qt::Key_X, Qt::ControlModifier);
    QCoreApplication::postEvent(m_mapScene, keyEvent);
}

void MainWindow::onCopy()
{
    qDebug() << "Copy.";
    // TODO it's not the best way to manage event.
    // Shortcut are good to be kept customisable. If we do so in the future,
    // we'll need to update all those methods. Future refacto : expose the event
    // to call and call it directly. And from the other way, use QShortcut (we
    // might need to set shortcutContext) instead of keypressevent
    QKeyEvent* keyEvent =
        new QKeyEvent(QEvent::KeyPress, Qt::Key_C, Qt::ControlModifier);
    QCoreApplication::postEvent(m_mapScene, keyEvent);
}

void MainWindow::onPaste()
{
    qDebug() << "Paste.";
    // TODO: it's not the best way to manage event.
    // Shortcut are good to be kept customisable. If we do so in the future,
    // we'll need to update all those methods. Future refacto : expose the event
    // to call and call it directly. And from the other way, use QShortcut (we
    // might need to set shortcutContext) instead of keypressevent
    QKeyEvent* keyEvent =
        new QKeyEvent(QEvent::KeyPress, Qt::Key_V, Qt::ControlModifier);
    QCoreApplication::postEvent(m_mapScene, keyEvent);
}

void MainWindow::removeTools()
{
    qDebug() << "Remove tools";
    m_mapScene->unsetDrawingTool();
    m_chipsetScene->unsetPaletteTool();
    m_ui->widgetDrawingToolbox->clear();
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

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (nullptr != m_currentProject) {
        QMessageBox::StandardButton resBtn = QMessageBox::question(
            this, "DummyEditor", tr("Do you want to save before you quit ?\n"),
            QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
            QMessageBox::Cancel);
        switch (resBtn) {
        case QMessageBox::Yes:
            saveProject();
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
