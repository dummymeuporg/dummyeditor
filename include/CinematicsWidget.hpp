#ifndef CINEMATICSWIDGET_H
#define CINEMATICSWIDGET_H

#include <QWidget>
#include <memory>

namespace Ui {
class CinematicsWidget;
}

class CinematicsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CinematicsWidget(QWidget* parent = nullptr);
    virtual ~CinematicsWidget() override; // we need this because of smart ptr + forward declaration..

private:
    std::unique_ptr<Ui::CinematicsWidget> m_ui;
};

#endif // CINEMATICSWIDGET_H
