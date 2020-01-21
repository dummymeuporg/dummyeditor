#include "CinematicsWidget.hpp"
#include "ui_CinematicsWidget.h"

CinematicsWidget::CinematicsWidget(QWidget *parent) :
                                                      QWidget(parent),
                                                      ui(new Ui::CinematicsWidget)
{
  ui->setupUi(this);
}

CinematicsWidget::~CinematicsWidget()
{
  delete ui;
}
