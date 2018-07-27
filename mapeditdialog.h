#ifndef MAPEDITDIALOG_H
#define MAPEDITDIALOG_H

#include <memory>

#include <QDialog>

#include "dummy/project.h"

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
    explicit MapEditDialog(std::shared_ptr<const Dummy::Project> project,
                           std::shared_ptr<const Dummy::Map> = nullptr,
                           QWidget *parent = nullptr);
    ~MapEditDialog();

    QString getMapName() const;
    quint16 getWidth() const;
    quint16 getHeight() const;
    QString getChipset() const;
    QString getMusic() const;

private:
    Ui::MapEditDialog *ui;
    const std::shared_ptr<const Dummy::Project> m_project;
private slots:
    void onChipsetBrowse();
    void onOK();
};

#endif // NEWMAPDIALOG_H
