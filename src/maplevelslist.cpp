#include "maplevelslist.hpp"
#include "ui_maplevelslist.h"

MapLevelsList::MapLevelsList(QWidget* parent)
    : QWidget(parent),
      ui(new Ui::MapLevelsList)
{
    ui->setupUi(this);
}
