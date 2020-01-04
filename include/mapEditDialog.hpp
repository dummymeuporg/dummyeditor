#ifndef MAPEDITDIALOG_H
#define MAPEDITDIALOG_H

#include <memory>

#include <QDialog>

#include "editor/project.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Dummy {
    class Map;
}

namespace Ui {
class MapEditDialog;
}

//////////////////////////////////////////////////////////////////////////////
//  MapEditDialog class
//////////////////////////////////////////////////////////////////////////////

class MapEditDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MapEditDialog(
        std::shared_ptr<const Editor::Project> project,
        std::shared_ptr<Misc::MapDocument> = nullptr,
        QWidget *parent = nullptr);
    ~MapEditDialog() override;

    QString getMapName() const;
    quint16 getWidth() const;
    quint16 getHeight() const;
    QString getChipset() const;
    QString getMusic() const;

private slots:
    void onChipsetBrowse();
    void onOK();

private:
    Ui::MapEditDialog *m_ui;
    const std::shared_ptr<const Editor::Project> m_project;
};

#endif MAPEDITDIALOG_H
