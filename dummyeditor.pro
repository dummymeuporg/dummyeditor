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
    misc/mapdocument.cpp \
    misc/maptreemodel.cpp \
    mapstreeview.cpp \
    dummy/layer.cpp \
    mapeditdialog.cpp

HEADERS += \
    mainwindow.h \
    dummy/project.h \
    dummy/map.h \
    chipsetgraphicsscene.h \
    misc/mapdocument.h \
    misc/maptreemodel.h \
    mapstreeview.h \
    dummy/layer.h \
    mapeditdialog.h

FORMS += \
    mainwindow.ui \
    mapeditdialog.ui

RESOURCES += \
    icons.qrc

