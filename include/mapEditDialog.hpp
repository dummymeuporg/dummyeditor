#ifndef MAPEDITDIALOG_H
#define MAPEDITDIALOG_H

#include <memory>

#include <QDialog>

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Ui {
class MapEditDialog;
}

namespace Editor {
class Project;
}

struct MapDocument;

//////////////////////////////////////////////////////////////////////////////
//  MapEditDialog class
//////////////////////////////////////////////////////////////////////////////

class MapEditDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MapEditDialog(QWidget* parent = nullptr);

    void setup(const Editor::Project& project, const MapDocument* = nullptr);

    QString getMapName() const;
    quint16 getWidth() const;
    quint16 getHeight() const;
    QString getChipset() const;
    QString getMusic() const;

public slots:
    void on_pushButtonBrowseChipset_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    bool inputsAreValid(QString* errorMessage = nullptr);
    std::unique_ptr<Ui::MapEditDialog> m_ui;
    QString m_chipsetPath;
};

#endif // MAPEDITDIALOG_H
