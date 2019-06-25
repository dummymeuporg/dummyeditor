#pragma once

#include <QDockWidget>

namespace Ui {
class MapLevelsListWidget;
}

class MapLevelsListWidget : public QDockWidget {
    Q_OBJECT
public:
    MapLevelsListWidget(QWidget* parent = nullptr);
private:
    Ui::MapLevelsListWidget* ui;
};
