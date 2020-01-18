#ifndef GENERALWINDOW_H
#define GENERALWINDOW_H

#include <QMainWindow>

namespace Ui {
class GeneralWindow;
}

class GeneralWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit GeneralWindow(QWidget *parent = nullptr);
  ~GeneralWindow();

private:
  Ui::GeneralWindow *m_ui;
};

#endif // GENERALWINDOW_H
