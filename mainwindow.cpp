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
        QFileDialog::getExistingDirectory(this,
                                          tr("Choose your project directory"));

    // Initialize a project into this directory
    _initializeProject(projectDirectory);

}

void MainWindow::openProject() {
    QString projectDirectory =
        QFileDialog::getExistingDirectory(
            this, tr("Choose an existing project directory"));

    Dummy::Project project(projectDirectory);

    ui->treeView->setModel(
        static_cast<QAbstractItemModel*>(project.mapsModel())
    );
}


void MainWindow::_initializeProject(const QString& projectDirectory) {
    Dummy::Project::create(projectDirectory);
}
