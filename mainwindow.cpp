#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QMessageBox>

#include "dummy/map.h"
#include "dummy/project.h"

#include "misc/maptreemodel.h"

#include "chipsetgraphicscene.h"
#include "mainwindow.h"
#include "newmapdialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_currentProject(nullptr),
    m_chipsetScene(nullptr)
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


    ui->tabGeneral->layout()->setMenuBar(tabGeneralToolBar);
    m_chipsetScene = new ChipsetGraphicsScene();
    ui->graphicsViewChipset->scale(2.0, 2.0);
    ui->graphicsViewChipset->setScene(m_chipsetScene);

    // XXX: Test
    m_chipsetScene->addPixmap(QPixmap("chipset/LhynnBis.png"));

}

void MainWindow::_closeCurrentProject() {
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

    // Initialize a project into this directory
    _initializeProject(projectDirectory);

    if (nullptr != m_currentProject) {
        _closeCurrentProject();
    }

    m_currentProject = std::shared_ptr<Dummy::Project>(
        new Dummy::Project(projectDirectory)
    );

    ui->treeViewMaps->setProject(m_currentProject);

}

void MainWindow::openProject() {

    if (nullptr != m_currentProject) {
        _closeCurrentProject();
    }

    QString projectDirectory =
        QFileDialog::getExistingDirectory(
            this, tr("Choose an existing project directory"));

    m_currentProject = std::shared_ptr<Dummy::Project>(
        new Dummy::Project(projectDirectory)
    );

    ui->treeViewMaps->setModel(
        static_cast<QAbstractItemModel*>(m_currentProject->mapsModel())
    );

    ui->treeViewMaps->setProject(m_currentProject);

}

void MainWindow::saveProject() {
    if (nullptr != m_currentProject) {
        m_currentProject->saveProjectFile();
    }
}


void MainWindow::_initializeProject(const QString& projectDirectory) {
    Dummy::Project::create(projectDirectory);
}

void MainWindow::selectCurrentMap(QModelIndex selectedIndex) {
    Misc::MapTreeModel* mapModel = m_currentProject->mapsModel();
    QString mapName(mapModel->itemFromIndex(selectedIndex)->text());
    qDebug() << mapName;
}
