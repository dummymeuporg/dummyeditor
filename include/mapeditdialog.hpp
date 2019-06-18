#pragma once
#include <memory>

#include <QDialog>

#include "editorproject.hpp"

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
        std::shared_ptr<const EditorProject> project,
        std::shared_ptr<const Dummy::Core::GraphicMap> = nullptr,
        QWidget *parent = nullptr);
    ~MapEditDialog() override;

    QString getMapName() const;
    quint16 getWidth() const;
    quint16 getHeight() const;
    QString getChipset() const;
    QString getMusic() const;

private:
    Ui::MapEditDialog *ui;
    const std::shared_ptr<const EditorProject> m_project;
private slots:
    void onChipsetBrowse();
    void onOK();
};
