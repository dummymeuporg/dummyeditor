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
    chipsetcell.cpp \
    mapcell.cpp

HEADERS += \
    mainwindow.h \
    dummy/project.h \
    misc/treeitem.h \
    misc/treemodel.h \
    chipsetcell.h \
    mapcell.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    icons.qrc
