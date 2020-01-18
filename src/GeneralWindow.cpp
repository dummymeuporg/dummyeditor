#include "GeneralWindow.hpp"
#include "ui_GeneralWindow.h"

GeneralWindow::GeneralWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_ui(new Ui::GeneralWindow)
{
    m_ui->setupUi(this);

    m_ui->splitter_map->setSizes({width() / 4, width() - (width() / 4)});
}

GeneralWindow::~GeneralWindow()
{
    delete m_ui;
}
