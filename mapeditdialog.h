#ifndef MAPEDITDIALOG_H
#define MAPEDITDIALOG_H

#include <memory>

#include <QDialog>

namespace Dummy {
    class Map;
}

namespace Ui {
class MapEditDialog;
}

class MapEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MapEditDialog(std::shared_ptr<const Dummy::Map> = nullptr,
                           QWidget *parent = 0);
    ~MapEditDialog();

    QString getMapName() const;
    quint16 getWidth() const;
    quint16 getHeight() const;
    QString getChipset() const;
    QString getMusic() const;

private:
    Ui::MapEditDialog *ui;
};

#endif // NEWMAPDIALOG_H
