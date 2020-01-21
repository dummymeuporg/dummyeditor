#ifndef CINEMATICSWIDGET_H
#define CINEMATICSWIDGET_H

#include <QWidget>

namespace Ui {
class CinematicsWidget;
}

class CinematicsWidget : public QWidget
{
  Q_OBJECT

public:
  explicit CinematicsWidget(QWidget *parent = nullptr);
  ~CinematicsWidget();

private:
  Ui::CinematicsWidget *ui;
};

#endif // CINEMATICSWIDGET_H
