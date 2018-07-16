QT += widgets
QT += core
QT += gui
QT += xml

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    dummy/project.cpp \
    misc/treeitem.cpp \
    misc/treemodel.cpp \
    dummy/map.cpp \
    newmapdialog.cpp \
    chipsetgraphicsscene.cpp \
    misc/mapdocument.cpp

HEADERS += \
    mainwindow.h \
    dummy/project.h \
    misc/treeitem.h \
    misc/treemodel.h \
    dummy/map.h \
    newmapdialog.h \
    chipsetgraphicscene.h \
    misc/mapdocument.h

FORMS += \
    mainwindow.ui \
    newmapdialog.ui

RESOURCES += \
    icons.qrc

