QT += widgets
QT += core
QT += gui
QT += xml

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    dummy/blockinglayer.cpp \
    dummy/project.cpp \
    dummy/map.cpp \
    chipsetgraphicsscene.cpp \
    graphicmap/mapgraphicsscene.cpp \
    misc/mapdocument.cpp \
    misc/maptreemodel.cpp \
    mapstreeview.cpp \
    dummy/layer.cpp \
    mapeditdialog.cpp \
    graphicmap/paintinglayerstate.cpp \
    graphicmap/notpaintingstate.cpp \
    graphicmap/firstlayerstate.cpp \
    graphicmap/secondlayerstate.cpp \
    graphicmap/thirdlayerstate.cpp \
    graphicmap/drawingtool.cpp \
    graphicmap/pendrawingtool.cpp \
    graphicmap/nodrawingtool.cpp \
    graphicmap/rectangledrawingtool.cpp \
    graphicmap/selectiondrawingtool.cpp \
    graphicmap/selectiondrawingclipboard.cpp \
    graphicmap/paintinggraphiclayerstate.cpp \
    graphicmap/blockinggraphiclayer.cpp \
    graphicmap/visiblegraphiclayer.cpp \
    graphicmap/graphiclayer.cpp \
    graphicmap/paintingblockinglayerstate.cpp \
    graphicmap/blockinglayerstate.cpp

HEADERS += \
    mainwindow.h \
    dummy/blockinglayer.h \
    dummy/project.h \
    dummy/map.h \
    chipsetgraphicsscene.h \
    graphicmap/mapgraphicsscene.h \
    misc/mapdocument.h \
    misc/maptreemodel.h \
    mapstreeview.h \
    dummy/layer.h \
    mapeditdialog.h \
    graphicmap/paintinglayerstate.h \
    graphicmap/notpaintingstate.h \
    graphicmap/firstlayerstate.h \
    graphicmap/secondlayerstate.h \
    graphicmap/thirdlayerstate.h \
    graphicmap/drawingtool.h \
    graphicmap/pendrawingtool.h \
    graphicmap/nodrawingtool.h \
    graphicmap/rectangledrawingtool.h \
    graphicmap/selectiondrawingtool.h \
    graphicmap/selectiondrawingclipboard.h \
    graphicmap/paintinggraphiclayerstate.h \
    graphicmap/blockinggraphiclayer.h \
    graphicmap/visiblegraphiclayer.h \
    graphicmap/graphiclayer.h \
    graphicmap/paintingblockinglayerstate.h \
    graphicmap/blockinglayerstate.h

FORMS += \
    mainwindow.ui \
    mapeditdialog.ui

RESOURCES += \
    icons.qrc

