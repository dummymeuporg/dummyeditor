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
    ~MapEditDialog() override;

    void setup(const Editor::Project& project,
               std::shared_ptr<MapDocument> = nullptr);

    QString getMapName() const;
    quint16 getWidth() const;
    quint16 getHeight() const;
    QString getChipset() const;
    QString getMusic() const;

private slots:
    void on_pushButtonBrowseChipset_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    bool inputsAreValid(QString* errorMessage = nullptr);
    Ui::MapEditDialog* m_ui = nullptr;
    QString m_chipsetPath;
};

#endif // MAPEDITDIALOG_H
