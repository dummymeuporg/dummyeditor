#include <QFileDialog>
#include <QMessageBox>

#include "editor/map.hpp"
#include "mapDocument.hpp"
#include "mapEditDialog.hpp"
#include "ui_mapeditdialog.h"

MapEditDialog::MapEditDialog(
    const std::shared_ptr<const Editor::Project> project,
    std::shared_ptr<MapDocument> mapDocument, QWidget* parent)
    : QDialog(parent)
    , m_ui(new Ui::MapEditDialog)
    , m_project(project)
{
    m_ui->setupUi(this);

    if (nullptr != mapDocument) {
        auto map(mapDocument->map());
        m_ui->lineEditMapName->setText(mapDocument->mapName());
        m_ui->lineEditChipset->setText(QString::fromStdString(map->chipset()));
        m_ui->lineEditMusic->setText(QString::fromStdString(map->music()));
        m_ui->spinBoxMapHeight->setValue(map->height());
        m_ui->spinBoxMapWidth->setValue(map->width());
    }
}

MapEditDialog::~MapEditDialog()
{
    delete m_ui;
}

QString MapEditDialog::getMapName() const
{
    return m_ui->lineEditMapName->text();
}

quint16 MapEditDialog::getWidth() const
{
    return m_ui->spinBoxMapWidth->value();
}

quint16 MapEditDialog::getHeight() const
{
    return m_ui->spinBoxMapHeight->value();
}

QString MapEditDialog::getChipset() const
{
    return m_ui->lineEditChipset->text();
}

QString MapEditDialog::getMusic() const
{
    return m_ui->lineEditMusic->text();
}

void MapEditDialog::onChipsetBrowse()
{
    QString chipsetPath = QString::fromStdString(
        (m_project->coreProject().projectPath() / "chipsets").string());

    // On Windows, fs::pash puts some backslashes. That sucks.
    // Clean path uses slashes, remove weird paths as "folder/../folder"
    chipsetPath = QDir::cleanPath(chipsetPath);

    QFileDialog dlg(this, tr("Choose the chipset file for your map."),
                    chipsetPath, "PNG files (*.png)");
    dlg.exec();

    if (dlg.result() == QDialog::Accepted) {
        QStringList selectedFiles = dlg.selectedFiles();
        QString selectedChipset   = selectedFiles.at(0);
        int index                 = selectedChipset.indexOf(chipsetPath);
        if (index < 0) {
            QMessageBox::critical(
                this, tr("Error"),
                tr("Please select a chipset inside the 'chipset' folder."));
        } else {
            m_ui->lineEditChipset->setText(
                selectedChipset.mid(index + 1 + chipsetPath.size()));
        }
    }
}

void MapEditDialog::onOK()
{
    if (m_ui->lineEditMapName->text() == "") {
        QMessageBox::critical(this, tr("Error"),
                              tr("You must enter a map name."));
    } else if (m_ui->lineEditChipset->text() == "") {
        QMessageBox::critical(this, tr("Error"),
                              tr("You must enter a chipset filename."));
    } else if (m_ui->spinBoxMapHeight->value() < 1) {
        QMessageBox::critical(
            this, tr("Error"),
            tr("You map's height must be above or equal to 1."));
    } else if (m_ui->spinBoxMapWidth->value() < 1) {
        QMessageBox::critical(
            this, tr("Error"),
            tr("You map's width must be above or equal to 1."));
    } else {
        accept();
    }
}
