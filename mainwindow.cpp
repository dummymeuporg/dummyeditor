#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QMessageBox>

#include "dummy/map.h"
#include "dummy/project.h"

#include "misc/maptreemodel.h"

#include "chipsetgraphicsscene.h"
#include "graphicmap/mapgraphicsscene.h"
#include "mainwindow.h"
#include "mapeditdialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_currentProject(nullptr),
    m_chipsetScene(nullptr),
    m_mapScene(nullptr)
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

    m_mapScene = new GraphicMap::MapGraphicsScene();
    ui->graphicsViewMap->scale(2.0, 2.0);
    ui->graphicsViewMap->setScene(m_mapScene);

    QObject::connect(ui->treeViewMaps, SIGNAL(chipsetMapChanged(QString)),
                     m_chipsetScene, SLOT(changeChipset(QString)));
    QObject::connect(m_chipsetScene, SIGNAL(selectionChanged(QRect)),
                     m_mapScene, SLOT(changeSelection(QRect)));

    QObject::connect(ui->actionLow_layer_1, SIGNAL(triggered(bool)),
                     m_mapScene, SLOT(showFirstLayer()));
    QObject::connect(ui->actionLow_layer_2, SIGNAL(triggered(bool)),
                     m_mapScene, SLOT(showSecondLayer()));
    QObject::connect(ui->actionHigh_layer, SIGNAL(triggered(bool)),
                     m_mapScene, SLOT(showThirdLayer()));

}

void MainWindow::_closeCurrentProject() {
    delete m_chipsetScene;
    delete m_mapScene;
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
        qDebug() << m_currentProject->openedMaps().count();
        if (m_currentProject->openedMaps().count() > 0) {
            QMap<QString, Misc::MapDocument>::iterator i;

            for(auto e : m_currentProject->openedMaps().keys()) {
                qDebug() << e;
                m_currentProject->document(e)->save();
            }
        }
    }
}


void MainWindow::_initializeProject(const QString& projectDirectory) {
    Dummy::Project::create(projectDirectory);
}

void MainWindow::selectCurrentMap(QModelIndex selectedIndex) {
    Misc::MapTreeModel* mapModel = m_currentProject->mapsModel();

    QString mapName(mapModel->itemFromIndex(selectedIndex)->text());
    qDebug() << mapName;
    std::shared_ptr<Dummy::Map> map(
        m_currentProject->document(mapName)->map());
    m_chipsetScene->setChipset(
        m_currentProject->fullpath() + "/chipsets/" + map->chipset()
    );
    m_mapScene->setMapDocument(m_currentProject->document(mapName));

    if (!ui->actionLow_layer_1->isChecked() &&
        !ui->actionLow_layer_2->isChecked() &&
            !ui->actionHigh_layer->isChecked()) {
        ui->actionLow_layer_1->trigger();
    }
    ui->graphicsViewChipset->viewport()->update();
}
