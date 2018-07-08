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

    /*----------------------tab GENERAL---------------------------------- */

    //add a toolbar in the top of gridlayout
    QToolBar *tabGeneralToolBar = new QToolBar();
    tabGeneralToolBar->setStyleSheet("QToolBar{background-color: #ABABAB;}");

    //create a group action to regroup action tools
    QActionGroup *toolsGroup = new QActionGroup(this);
    toolsGroup->addAction("Working tool");
    toolsGroup->addAction(ui->actionSelection);
    toolsGroup->addAction(ui->actionPen);
    toolsGroup->addAction(ui->actionRectangle);
    tabGeneralToolBar->addActions(toolsGroup->actions());

    tabGeneralToolBar->addSeparator();

    //create a group action to regroup action layers
    QActionGroup *layersGroup = new QActionGroup(this);
    layersGroup->addAction("Working layer");
    layersGroup->addAction(ui->actionLow_layer_1);
    layersGroup->addAction(ui->actionLow_layer_2);
    layersGroup->addAction(ui->actionHigh_layer);
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


    ui->tabGeneralGridLayout->setMenuBar(tabGeneralToolBar);

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

//void MainWindow::openProject() {
//    QString projectDirectory =
//        QFileDialog::getExistingDirectory(
//            this, tr("Choose an existing project directory"));

//    Dummy::Project project(projectDirectory);

//    ui->treeView->setModel(
//        static_cast<QAbstractItemModel*>(project.mapsModel())
//    );
//}


void MainWindow::_initializeProject(const QString& projectDirectory) {
    // Create project.xml
    // Create maps folder
    // Create chipset folder
    // Create sound folder

    Dummy::Project::create(projectDirectory);
}
