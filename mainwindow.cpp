#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

#include "dummy/project.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newProject() {
    // Open a file dialog to select a folder
    QString projectDirectory =
            QFileDialog::getExistingDirectory(
                this, tr("Choose your project directory"));

    QMessageBox::information(this, tr("Info"), projectDirectory);

    // Initialize a project into this directory
    _initializeProject(projectDirectory);

}


void MainWindow::_initializeProject(const QString& projectDirectory) {
    // Create project.xml
    // Create maps folder
    // Create chipset folder
    // Create sound folder

    Dummy::Project::create(projectDirectory);
}
