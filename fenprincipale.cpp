#include "FenPrincipale.h"

FenPrincipale::FenPrincipale()
{

    setWindowTitle("Editeur de carte");
    setWindowIcon(QIcon("Icone.png"));


//création de la barre des menus
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");

        QAction *actionNouveau = new QAction("&Nouveau", this);
        menuFichier->addAction(actionNouveau);
        actionNouveau->setShortcut(QKeySequence("Ctrl+N"));
        actionNouveau->setIcon(QIcon("Nouveau.png"));
        //connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

        QAction *actionOuvrir = new QAction("&Ouvrir cartes", this);
        menuFichier->addAction(actionOuvrir);
        actionOuvrir->setShortcut(QKeySequence("Ctrl+O"));
        actionOuvrir->setIcon(QIcon("Ouvrir.png"));
        //connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

        QAction *actionEnregistrer = new QAction("&Enregistrer", this);
        menuFichier->addAction(actionEnregistrer);
        actionEnregistrer->setShortcut(QKeySequence("Ctrl+S"));
        actionEnregistrer->setIcon(QIcon("Enregistrer.png"));
        //connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

        menuFichier->addSeparator();

        QAction *actionImporterProjet = new QAction("Importer un &projet", this);
        menuFichier->addAction(actionImporterProjet);

        QAction *actionImporterCarte = new QAction("Importer une &carte", this);
        menuFichier->addAction(actionImporterCarte);

        menuFichier->addSeparator();

        //nettoyer le projet, carte sans parent, effacer perso test...

        QAction *actionQuitter = new QAction("&Quitter", this);
        menuFichier->addAction(actionQuitter);
        actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
        actionQuitter->setIcon(QIcon("Quitter.png"));
        connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

    QMenu *menuEdition = menuBar()->addMenu("&Edition");

        QAction *actionAnnuler = new QAction("&Annuler", this);
        menuEdition->addAction(actionAnnuler);
        actionAnnuler->setShortcut(QKeySequence("Ctrl+Z"));
        actionAnnuler->setIcon(QIcon("Annuler.png"));

        menuEdition->addSeparator();

        QAction *actionCopier = new QAction("&Copier", this);
        menuEdition->addAction(actionCopier);
        actionCopier->setShortcut(QKeySequence("Ctrl+C"));
        actionCopier->setIcon(QIcon("Copier.png"));

        QAction *actionColler = new QAction("Coll&er", this);
        menuEdition->addAction(actionColler);
        actionColler->setShortcut(QKeySequence("Ctrl+V"));
        actionColler->setIcon(QIcon("Coller.png"));


    QMenu *menuMAJ = menuBar()->addMenu("&Mise à jour d'un projet");

    QMenu *menuAide = menuBar()->addMenu("&Aide");


//création de la barre d'outils
    QToolBar *toolBarFichier = addToolBar("Fichier");

    toolBarFichier->addAction(actionNouveau);
    toolBarFichier->addAction(actionOuvrir);
    toolBarFichier->addAction(actionEnregistrer);

    toolBarFichier->addSeparator();

    toolBarFichier->addAction(actionQuitter);

    toolBarFichier->addSeparator();

    toolBarFichier->addAction(actionAnnuler);

    toolBarFichier->addSeparator();

    toolBarFichier->addAction(actionColler);
    toolBarFichier->addAction(actionCopier);

    toolBarFichier->addSeparator();

    QSlider *zoom = new QSlider(Qt::Horizontal, this);
    toolBarFichier->addWidget(zoom);


//création de la zone centrale qui peut afficher plusieurs fenêtres

    QWidget *zoneCentrale = new QWidget;
    setCentralWidget(zoneCentrale);

    QTabWidget *onglets = new QTabWidget(zoneCentrale);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addWidget(onglets);
    zoneCentrale->setLayout(layoutPrincipal);

    QWidget *general = new QWidget;
    QWidget *chipset = new QWidget;
    QWidget *monstre = new QWidget;
    QWidget *zoneDeMonstre = new QWidget;

    onglets->addTab(general, "Général");
    onglets->addTab(chipset, "Chipset");
    onglets->addTab(monstre, "Monstre");
    onglets->addTab(zoneDeMonstre, "Zone de monstre");


    QLabel  *label_img  = new QLabel(general);
    QPixmap *pixmap_img = new QPixmap("LhynnBis.png");
         label_img->setPixmap(*pixmap_img);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(label_img,0,0);
    general->setLayout(gridLayout);

    QStatusBar *statusBar = new QStatusBar;
    layoutPrincipal->addWidget(statusBar);

    statusBar->showMessage(tr("Status bar : Tout va bien navette"));
}
