#include "GeneralWindow.hpp"
#include "ui_GeneralWindow.h"

#include <QCloseEvent>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

#include "chipsetGraphicsScene.hpp"
#include "editor/project.hpp"
#include "graphicMap/mapGraphicsScene.hpp"

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
    m_ui->graphicsViewMap->setScene(m_mapScene.get());

    // Set default sizes of movable splitters between panels
    m_ui->splitter_map->setSizes({width() / 4, width() - (width() / 4)});
    m_ui->splitter_chipset->setSizes({height() / 3, height() - (height() / 3)});

    // Set default view state
    updateProjectView();

    // UI items connections and shortcuts
    connect(m_ui->btnNewMap, SIGNAL(clicked()), m_ui->mapList,
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
    connect(m_ui->btnNewMap, SIGNAL(clicked()), m_ui->mapList,
            SLOT(addMapAtRoot()));
    connect(m_ui->mapList, SIGNAL(chipsetMapChanged(QString)),
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
    updateMapsList();

    // TODO update usable actions
    m_ui->actionSave->setEnabled(thereIsAProject);
    m_ui->actionClose->setEnabled(thereIsAProject);
}

void GeneralWindow::updateMapsList()
{
    if (m_loadedProject == nullptr) {
        m_ui->mapList->clear();
    } else {
        m_ui->mapList->setProject(m_loadedProject);
    }
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
    bool projectOpened = loadProject(projectDirectory);
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
