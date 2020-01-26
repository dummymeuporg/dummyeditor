#include "GeneralWindow.hpp"
#include "ui_GeneralWindow.h"

#include <QCloseEvent>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

#include "editor/layerBlocking.hpp"
#include "editor/layerGraphic.hpp"
#include "editor/map.hpp"
#include "editor/project.hpp"
#include "graphicMap/layerGraphicBlocking.hpp"
#include "graphicMap/layerGraphicVisible.hpp"
#include "utils/definitions.hpp"
#include "utils/mapDocument.hpp"

using Editor::Project;

//////////////////////////////////////////////////////////////////////////////

GeneralWindow::GeneralWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_ui(new Ui::GeneralWindow)
    , m_mapTools(m_chipsetScene, m_mapScene, m_ui.get())
{
    m_ui->setupUi(this);
    setupLoggers();

    m_ui->graphicsViewChipset->setScene(&m_chipsetScene);
    m_ui->graphicsViewChipset->scale(2.0, 2.0);

    m_ui->graphicsViewMap->setScene(&m_mapScene);
    m_ui->graphicsViewMap->scale(2.0, 2.0);
    m_ui->graphicsViewMap->setBackgroundBrush(QColor("#969696"));

    // Set default sizes of movable splitters between panels
    QList<int> horiCoef = {width() / 4, width() - (width() / 4)};
    QList<int> vertCoef = {width() / 4, width() - (width() / 4)};
    m_ui->splitter_map->setSizes(horiCoef);
    m_ui->splitter_chipset->setSizes(vertCoef);

    // Set default view state
    updateProjectView();

    // UI items connections and shortcuts

    m_ui->actionNew->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    m_ui->actionNew->setShortcutContext(Qt::ApplicationShortcut);

    m_ui->actionOpen->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    m_ui->actionOpen->setShortcutContext(Qt::ApplicationShortcut);

    m_ui->actionSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    m_ui->actionSave->setShortcutContext(Qt::ApplicationShortcut);

    m_ui->actionClose->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    m_ui->actionClose->setShortcutContext(Qt::ApplicationShortcut);

    m_ui->actionCut->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    m_ui->actionCut->setShortcutContext(Qt::ApplicationShortcut);

    m_ui->actionCopy->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    m_ui->actionCopy->setShortcutContext(Qt::ApplicationShortcut);

    m_ui->actionPaste->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    m_ui->actionPaste->setShortcutContext(Qt::ApplicationShortcut);

    // connect ui items
    connect(m_ui->btnNewMap, SIGNAL(clicked()), m_ui->mapsList, SLOT(addMapAtRoot()));
    connect(m_ui->mapsList, SIGNAL(chipsetMapChanged(QString)), &m_chipsetScene, SLOT(setChipset(QString)));
}

GeneralWindow::~GeneralWindow()
{
    cleanLoggers();
}

//////////////////////////////////////////////////////////////////////////////

void GeneralWindow::closeEvent(QCloseEvent* event)
{
    bool closingAccepted = closeProject();

    if (closingAccepted)
        event->accept();
    else
        event->ignore();
}

bool GeneralWindow::loadProject(const QString& path)
{
    // Create a new project
    std::string strPath = QDir::cleanPath(path).toStdString();
    auto newProject     = std::make_shared<Project>(strPath);

    // Check if has been successfully loaded
    // TODO add a "isLoaded" method to check loading errors
    // if not loaded, return false here

    // Use this new project
    m_loadedProject = newProject;

    // Update the view
    updateProjectView();

    // TODO: add the project name and the path to the output
    if (nullptr != m_loadedProject)
        Log::debug(tr("Project loaded"));

    return true;
}

bool GeneralWindow::closeProject()
{
    if (m_loadedProject == nullptr)
        return true; // success, nothing to do

    QMessageBox::StandardButton resBtn =
        QMessageBox::question(this, "DummyEditor", tr("Do you want to save before closing this project?"),
                              QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::Cancel);

    // Save project if needed
    if (resBtn == QMessageBox::Yes) {
        m_loadedProject->saveProject();
    } else if (resBtn == QMessageBox::No) {
        // Nothing to do
    } else {
        Log::debug(tr("Closing canceled"));
        return false; // failure of closing : cancellation
    }

    // Clear project
    m_loadedProject = nullptr;
    Log::debug(tr("Project closed"));

    // Clear view
    updateProjectView();

    return true; // success, we closed and cleaned
}

void GeneralWindow::updateProjectView()
{
    bool thereIsAProject = (m_loadedProject != nullptr);

    // Disable unusable components
    m_ui->panels_tabs->setEnabled(thereIsAProject);
    m_ui->toolbar_gameTool->setEnabled(thereIsAProject);
    if (! thereIsAProject) {
        m_mapTools.clear();
        m_ui->toolbar_mapTools->setEnabled(false);
    }

    // update tabs content
    updateMapsAndFloorsList();

    // update usable actions
    m_ui->actionSave->setEnabled(thereIsAProject);
    m_ui->actionClose->setEnabled(thereIsAProject);
}

void GeneralWindow::updateMapsAndFloorsList()
{
    if (m_loadedProject == nullptr) {
        m_ui->mapsList->clear();
    } else {
        m_ui->mapsList->setProject(m_loadedProject);
    }
    m_ui->maps_panel->setCurrentIndex(0);
    m_ui->layer_list_tab->reset();
    m_mapScene.clear();
    m_chipsetScene.clear();
}

void GeneralWindow::setupLoggers()
{
    // Console logger
    std::shared_ptr<Log::Logger> pConsoleLog = std::make_shared<Log::LoggerConsole>();
    m_loggers.push_back(pConsoleLog);
    Log::Logger::registerLogger(pConsoleLog);

    // Status bar Logger
    std::shared_ptr<Log::Logger> pStatusBarLog = std::make_shared<LoggerStatusBar>(m_ui->statusbar);
    m_loggers.push_back(pStatusBarLog);
    Log::Logger::registerLogger(pStatusBarLog);

    // File logger

    std::shared_ptr<Log::Logger> pFileLog = std::make_shared<Log::LoggerFile>();
    m_loggers.push_back(pFileLog);
    Log::Logger::registerLogger(pFileLog);
}

void GeneralWindow::cleanLoggers()
{
    for (const auto& pLogger : m_loggers)
        Log::Logger::unregisterLogger(pLogger);
    m_loggers.clear();
}

//////////////////////////////////////////////////////////////////////////////

void GeneralWindow::on_actionNew_triggered()
{
    // Open a file dialog to select a folder
    QString projectDirectory = QFileDialog::getExistingDirectory(this, tr("Choose your project directory"));

    if (projectDirectory == "")
        return;

    bool projectClosed = closeProject();
    if (! projectClosed)
        return;

    // Initialize a project into this directory
    Editor::Project::create(projectDirectory);

    // TODO: add the project name and the path to the output
    if (nullptr != m_loadedProject)
        Log::debug(tr("Project created"));

    loadProject(projectDirectory);
}

void GeneralWindow::on_actionOpen_triggered()
{
    // Close current project
    bool projectClosed = closeProject();
    if (! projectClosed)
        return;

    // Ask where new is
    QString projectDirectory = QFileDialog::getExistingDirectory(this, tr("Choose an existing project directory"));
    if (projectDirectory == "")
        return;

    // Open new
    loadProject(projectDirectory);
}

void GeneralWindow::on_actionSave_triggered()
{
    if (nullptr == m_loadedProject)
        return;

    // Save current project
    m_loadedProject->saveProject();

    // TODO: create a way to check the save action and get this info to
    // condition the output info
    Log::info(tr("Project saved"));
}

void GeneralWindow::on_actionClose_triggered()
{
    closeProject();
}

void GeneralWindow::on_mapsList_doubleClicked(const QModelIndex& selectedIndex)
{
    // fetch map data
    const MapsTreeModel* mapModel = m_loadedProject->mapsModel();
    QString mapName               = mapModel->itemFromIndex(selectedIndex)->text();
    const auto& mapData           = m_loadedProject->document(mapName).m_map;
    std::shared_ptr<Editor::Map> map(mapData);

    // update chipset scene
    QString chipsetPath =
        QString::fromStdString((m_loadedProject->coreProject().projectPath() / "chipsets" / map->chipset()).string());
    m_chipsetScene.setChipset(chipsetPath);
    m_ui->graphicsViewChipset->viewport()->update();

    // update map scene
    m_mapScene.setFloors(mapData->floors(), m_chipsetScene.chipset());
    m_ui->graphicsViewMap->setSceneRect(QRect(0, 0, map->width() * CELL_W, map->height() * CELL_H));

    // link visible layers
    for (const auto& pVisLayer : m_mapScene.graphicLayers()) {
        connect(pVisLayer.get(), SIGNAL(layerSelected(GraphicMap::VisibleGraphicLayer*)), this,
                SLOT(graphicLayerSelected(GraphicMap::VisibleGraphicLayer*)));
    }

    // link blocking layers
    for (const auto& pBlockLayer : m_mapScene.blockingLayers()) {
        connect(pBlockLayer.get(), SIGNAL(layerSelected(GraphicMap::BlockingGraphicLayer*)), this,
                SLOT(blockingLayerSelected(GraphicMap::BlockingGraphicLayer*)));
    }

    // link events layers ?

    m_mapTools.clear();

    // update layer list
    m_ui->layer_list_tab->setEditorMap(map);
    m_ui->maps_panel->setCurrentIndex(1);
}

void GeneralWindow::graphicLayerSelected(GraphicMap::VisibleGraphicLayer* visLayer)
{
    m_ui->toolbar_mapTools->setEnabled(true);
    m_mapTools.setActiveLayer(visLayer);
}
void GeneralWindow::blockingLayerSelected(GraphicMap::BlockingGraphicLayer* blockLayer)
{
    m_ui->toolbar_mapTools->setEnabled(true);
    m_mapTools.setActiveLayer(blockLayer);
}

void GeneralWindow::on_actionEraser_triggered()
{
    m_mapTools.setEraser();
}

void GeneralWindow::on_actionPen_triggered()
{
    m_mapTools.setPen();
}

void GeneralWindow::on_actionSelection_triggered()
{
    m_mapTools.setSelection();
}

void GeneralWindow::on_actionToggleGrid_triggered()
{
    m_mapTools.updateGridDisplay();
}

void GeneralWindow::on_actionCut_triggered()
{
    Log::debug(tr("TODO : Action Cut"));
}

void GeneralWindow::on_actionCopy_triggered()
{
    Log::debug(tr("TODO : Action Copy"));
}

void GeneralWindow::on_actionPaste_triggered()
{
    Log::debug(tr("TODO : Action Paste"));
}

//////////////////////////////////////////////////////////////////////////////

LoggerStatusBar::LoggerStatusBar(QStatusBar* stsBar)
    : m_statusBar(stsBar)
{}

void LoggerStatusBar::print(const std::string& message, Log::eLogType type)
{
    switch (type) {
    case Log::eLogType::INFORMATION:
    case Log::eLogType::ERROR:
        m_statusBar->showMessage(QString::fromStdString(message));
        break;
    case Log::eLogType::LOG:
    case Log::eLogType::DEBUG:
    default:
        break; // do nothing log default and unknown types
    }
}
