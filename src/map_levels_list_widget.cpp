#include "map_levels_list_widget.hpp"
#include "ui_map_levels_list_widget.h"

MapLevelsListWidget::MapLevelsListWidget(QWidget* parent)
    : QDockWidget(parent),
      ui(new Ui::MapLevelsListWidget)
{
    ui->setupUi(this);
}
