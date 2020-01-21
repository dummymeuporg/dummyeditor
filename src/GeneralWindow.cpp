#include "GeneralWindow.hpp"
#include "ui_GeneralWindow.h"

#include <QCloseEvent>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

#include "chipsetGraphicsScene.hpp"
#include "definitions.hpp"
#include "editor/map.hpp"
#include "editor/project.hpp"
#include "graphicMap/mapGraphicsScene.hpp"
#include "mapDocument.hpp"

using Editor::Project;

//////////////////////////////////////////////////////////////////////////////

GeneralWindow::GeneralWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_ui(new Ui::GeneralWindow)
    , m_chipsetScene(new ChipsetGraphicsScene)
    , m_mapScene(new GraphicMap::MapGraphicsScene)
{
    m_ui->setupUi(this);

    m_ui->graphicsViewChipset->setScene(m_chipsetScene.get());
    m_ui->graphicsViewChipset->scale(2.0, 2.0);

    m_ui->graphicsViewMap->setScene(m_mapScene.get());
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
    connect(m_ui->btnNewMap, SIGNAL(clicked()), m_ui->mapsList,
            SLOT(addMapAtRoot()));

    m_ui->actionNew->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    m_ui->actionNew->setShortcutContext(Qt::ApplicationShortcut);

    m_ui->actionOpen->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    m_ui->actionOpen->setShortcutContext(Qt::ApplicationShortcut);

    m_ui->actionSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    m_ui->actionSave->setShortcutContext(Qt::ApplicationShortcut);

    m_ui->actionClose->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    m_ui->actionClose->setShortcutContext(Qt::ApplicationShortcut);

    // connect ui items
    connect(m_ui->btnNewMap, SIGNAL(clicked()), m_ui->mapsList,
            SLOT(addMapAtRoot()));
    connect(m_ui->mapsList, SIGNAL(chipsetMapChanged(QString)),
            m_chipsetScene.get(), SLOT(changeChipset(QString)));
}

GeneralWindow::~GeneralWindow() {}

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
        qDebug() << "Project loaded" << endl;

    return true;
}

bool GeneralWindow::closeProject()
{
    if (m_loadedProject == nullptr)
        return true; // success, nothing to do

    QMessageBox::StandardButton resBtn = QMessageBox::question(
        this, "DummyEditor",
        tr("Do you want to save before closing this project?"),
        QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
        QMessageBox::Cancel);

    // Save project if needed
    if (resBtn == QMessageBox::Yes) {
        m_loadedProject->saveProject();
    } else if (resBtn == QMessageBox::No) {
        // Nothing to do
    } else {
        qDebug() << "Closing canceled" << endl;
        return false; // failure of closing : cancellation
    }

    // Clear project
    m_loadedProject = nullptr;
    qDebug() << "Project closed" << endl;

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
    m_ui->toolbar_mapTools->setEnabled(thereIsAProject);

    // TODO update tabs content
    updateMapsAndFloorsList();

    // TODO update usable actions
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
    m_ui->layer_list_tab->reset();
}

//////////////////////////////////////////////////////////////////////////////

void GeneralWindow::on_actionNew_triggered()
{
    // Open a file dialog to select a folder
    QString projectDirectory = QFileDialog::getExistingDirectory(
        this, tr("Choose your project directory"));

    if (projectDirectory == "")
        return;

    bool projectClosed = closeProject();
    if (! projectClosed)
        return;

    // Initialize a project into this directory
    Editor::Project::create(projectDirectory);

    // TODO: add the project name and the path to the output
    if (nullptr != m_loadedProject)
        qDebug() << "Project created" << endl;

    loadProject(projectDirectory);
}

void GeneralWindow::on_actionOpen_triggered()
{
    // Close current project
    bool projectClosed = closeProject();
    if (! projectClosed)
        return;

    // Ask where new is
    QString projectDirectory = QFileDialog::getExistingDirectory(
        this, tr("Choose an existing project directory"));
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
    qDebug() << "Project saved" << endl;
}

void GeneralWindow::on_actionClose_triggered()
{
    closeProject();
}

void GeneralWindow::on_mapsList_doubleClicked(const QModelIndex& selectedIndex)
{
    // fetch map data
    const MapsTreeModel* mapModel = m_loadedProject->mapsModel();
    QString mapName = mapModel->itemFromIndex(selectedIndex)->text();
    std::shared_ptr<Editor::Map> map(m_loadedProject->document(mapName)->m_map);

    // update chipset scene
    QString chipsetPath =
        QString::fromStdString((m_loadedProject->coreProject().projectPath()
                                / "chipsets" / map->chipset())
                                   .string());
    m_chipsetScene->setChipset(chipsetPath);
    m_ui->graphicsViewChipset->viewport()->update();

    // update map scene
    m_mapScene->setMapDocument(m_loadedProject->document(mapName));
    m_ui->graphicsViewMap->setSceneRect(
        QRect(0, 0, map->width() * CELL_W, map->height() * CELL_H));

    // TODO connect layer selection to toolbox setting

    // update layer list
    m_ui->layer_list_tab->setEditorMap(map);
    m_ui->maps_panel->setCurrentIndex(1);
}
