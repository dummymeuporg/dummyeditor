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

    QPushButton *billy = new QPushButton("Je suis billy");
    ui->tabGeneralGridLayout->addWidget(billy,0,0);

    //mon image de base

    chipsetBase = new QPixmap("LhynnBis.png");

/* --------------------- partie chipset --------------------------*/

    //layout pour avoir une grille chipset
    QGridLayout *gridLayoutChipset = new QGridLayout;
    gridLayoutChipset->setSpacing(0);

    // taille du chipset
    int tailleX = chipsetBase->width()/16;
    int tailleY = chipsetBase->height()/16;

    //definition du tableau de label
    chipsetCell ***label;
    label = new chipsetCell**[tailleX];
    for(int i=0;i<tailleX;i++)
    {
        label[i]=new chipsetCell*[tailleY];
    }
    for(int i=0;i<tailleX;i++)
    {
        for(int j=0;j<tailleY;j++)
        {
            label[i][j]=new chipsetCell;
            connect(label[i][j], SIGNAL(envoiCoord(int, int)), this, SLOT(receptionCoord(int, int)));
            label[i][j]->setText("");
            label[i][j]->setPixmap(chipsetBase->copy(16*i,16*j,16,16));
            label[i][j]->setFrameStyle(QFrame::Box);
            label[i][j]->setLineWidth(1);
            label[i][j]->setCoordX(i);
            label[i][j]->setCoordY(j);
            gridLayoutChipset->addWidget(label[i][j],j,i);
        }
    }

    //dans un scrollarea on ne peut mettre qu'un widget et pas un layout, on créé donc un widget inutile
    QWidget *widgetBidon = new QWidget;
    widgetBidon->setLayout(gridLayoutChipset);

    //création de la QScrollArea
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Light);
    scrollArea->setWidget(widgetBidon);

    //ajout de la scrollArea dans la partie gauche
    ui->tabGeneralGridLayout->addWidget(scrollArea,0,0);

   /* --------------------- partie map --------------------------*/

       //layout pour avoir une grille map
       QGridLayout *gridLayoutbis = new QGridLayout;
       gridLayoutbis->setSpacing(0);

       //definition de la liste de label

       QList<mapCell *> colonneTemporaire;

       for(int j=0 ; j<tailleY ; j++)
       {
           colonneTemporaire.append(new mapCell);
       }

       for(int i=0;i<tailleX;i++)
       {
           labelbis.append(colonneTemporaire);

           for(int j=0;j<tailleY;j++)
           {
               labelbis[i][j] = new mapCell;
               connect(labelbis[i][j], SIGNAL(envoiCoord(int, int)), this, SLOT(coloriage(int,int)));
               connect(labelbis[i][j], SIGNAL(envoiEtatSouris(bool)), this, SLOT(receptionEtatSouris(bool)));
               labelbis[i][j]->setPixmap(chipsetBase->copy(0,0,16,16));
               labelbis[i][j]->setFrameStyle(QFrame::Box);
               labelbis[i][j]->setLineWidth(1);
               labelbis[i][j]->setCoordX(i);
               labelbis[i][j]->setCoordY(j);
   //            qDebug()<<labelbis[i][j]->CoordX()<< labelbis[i][j]->CoordY();
               gridLayoutbis->addWidget(labelbis[i][j],j,i);
               //scene.addItem(labelbis[i][j]);
           }
       }


       //dans un scrollarea on ne peut mettre qu'un widget et pas un layout, on créé donc un widget inutile
       QWidget *principalWidgetMap = new QWidget;
       principalWidgetMap->setLayout(gridLayoutbis);


       //création de la QScrollArea

       QScrollArea *scrollAreabis = new QScrollArea;
       scrollAreabis->setBackgroundRole(QPalette::Light);
       scrollAreabis->setWidget(principalWidgetMap);
       scrollArea->setMouseTracking(true);

       //ajout de la scrollArea dans la partie droite
       ui->tabGeneralGridLayout->addWidget(scrollAreabis,0,1);

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

void MainWindow::receptionCoord(int coordX, int coordY)
{
    m_coordXactif = coordX;
    m_coordYactif = coordY;

    //statusBar->showMessage(tr("Cellule chipset active : X=") + QString::number(m_coordXactif) + " Y= " + QString::number(m_coordYactif));
}

void MainWindow::coloriage(int coordX, int coordY)
{
    qDebug("coloriage");
    qDebug()<<m_testSouris << coordX << coordY;

    if (m_testSouris == true)
    {
        labelbis[coordX][coordY]->setPixmap(chipsetBase->copy(16*m_coordXactif,16*m_coordYactif,16,16));
    }
}

void MainWindow::receptionEtatSouris(bool etatSouris)
{
        m_testSouris = etatSouris;
}
