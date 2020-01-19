#include "GeneralWindow.hpp"
#include "ui_GeneralWindow.h"

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

#include "editor/project.hpp"

using Editor::Project;

//////////////////////////////////////////////////////////////////////////////

GeneralWindow::GeneralWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_ui(new Ui::GeneralWindow)
{
    m_ui->setupUi(this);

    // Set default sizes of movable splitters between panels
    m_ui->splitter_map->setSizes({width() / 4, width() - (width() / 4)});

    // Set default view state
    updateProjectView();
}

GeneralWindow::~GeneralWindow()
{
    delete m_ui;
}

//////////////////////////////////////////////////////////////////////////////

bool GeneralWindow::loadProject(const QString& path)
{
    // Create a new project
    std::string strPath = QDir::cleanPath(path).toStdString();
    auto newProject     = std::unique_ptr<Project>(new Project(strPath));

    // Check if has been successfully loaded
    // TODO add a "isLoaded" method to check loading errors
    // if not loaded, return false here

    // Use this new project
    m_loadedProject = std::move(newProject);

    // Update the view
    updateProjectView();

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
        return false; // failure of closing : cancellation
    }

    // Clear project
    m_loadedProject = nullptr;

    // Clear view
    updateProjectView();

    return true; // success, we closed and cleaned
}

void GeneralWindow::updateProjectView()
{
    // Disable unusable components
    bool thereIsAProject = (m_loadedProject != nullptr);
    m_ui->panels_tabs->setEnabled(thereIsAProject);
    m_ui->toolbar_gameTool->setEnabled(thereIsAProject);
    m_ui->toolbar_mapTools->setEnabled(thereIsAProject);

    // TODO update tabs content
    // TODO update usable actions
}

//////////////////////////////////////////////////////////////////////////////

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
