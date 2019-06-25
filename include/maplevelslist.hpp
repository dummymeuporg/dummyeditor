#pragma once

#include <QWidget>

namespace Ui {
class MapLevelsList;
}

class MapLevelsList : public QWidget {
    Q_OBJECT
public:
    MapLevelsList(QWidget* parent = nullptr);
private:
    Ui::MapLevelsList* ui;
};
