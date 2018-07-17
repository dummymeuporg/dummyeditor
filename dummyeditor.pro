QT += widgets
QT += core
QT += gui
QT += xml

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    dummy/project.cpp \
    dummy/map.cpp \
    newmapdialog.cpp \
    chipsetgraphicsscene.cpp \
    misc/mapdocument.cpp \
    misc/maptreemodel.cpp

HEADERS += \
    mainwindow.h \
    dummy/project.h \
    dummy/map.h \
    newmapdialog.h \
    chipsetgraphicscene.h \
    misc/mapdocument.h \
    misc/maptreemodel.h

FORMS += \
    mainwindow.ui \
    newmapdialog.ui

RESOURCES += \
    icons.qrc

