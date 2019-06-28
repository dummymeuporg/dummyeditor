#pragma once
#include <memory>

#include <QDialog>

#include "editor/project.hpp"

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

private:
    Ui::MapEditDialog *ui;
    const std::shared_ptr<const Editor::Project> m_project;
private slots:
    void onChipsetBrowse();
    void onOK();
};
