#ifndef NEWMAPDIALOG_H
#define NEWMAPDIALOG_H

#include <QDialog>

namespace Dummy {
    class Map;
}

namespace Ui {
class NewMapDialog;
}

class NewMapDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewMapDialog(QWidget *parent = 0, const Dummy::Map* = nullptr);
    ~NewMapDialog();

    QString getMapName() const;
    quint16 getWidth() const;
    quint16 getHeight() const;
    QString getChipset() const;
    QString getMusic() const;

private:
    Ui::NewMapDialog *ui;
};

#endif // NEWMAPDIALOG_H
