#include "CinematicsWidget.hpp"
#include "ui_CinematicsWidget.h"

CinematicsWidget::CinematicsWidget(QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::CinematicsWidget)
{
    m_ui->setupUi(this);
}
