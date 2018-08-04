QT += widgets
QT += core
QT += gui
QT += xml

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    dummy/project.cpp \
    dummy/map.cpp \
    chipsetgraphicsscene.cpp \
    graphicmap/mapgraphicsscene.cpp \
    misc/mapdocument.cpp \
    misc/maptreemodel.cpp \
    mapstreeview.cpp \
    dummy/layer.cpp \
    mapeditdialog.cpp \
    graphicmap/graphiclayer.cpp

HEADERS += \
    mainwindow.h \
    dummy/project.h \
    dummy/map.h \
    chipsetgraphicsscene.h \
    graphicmap/mapgraphicsscene.h \
    misc/mapdocument.h \
    misc/maptreemodel.h \
    mapstreeview.h \
    dummy/layer.h \
    mapeditdialog.h \
    graphicmap/graphiclayer.h

FORMS += \
    mainwindow.ui \
    mapeditdialog.ui

RESOURCES += \
    icons.qrc

