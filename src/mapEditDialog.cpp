#include "mapEditDialog.hpp"
#include "ui_mapeditdialog.h"

#include <QFileDialog>
#include <QMessageBox>

#include "editor/map.hpp"
#include "editor/project.hpp"
#include "utils/mapDocument.hpp"


MapEditDialog::MapEditDialog(QWidget* parent)
    : QDialog(parent)
    , m_ui(new Ui::MapEditDialog)
{
    m_ui->setupUi(this);
}

void MapEditDialog::setup(const Editor::Project& project, const MapDocument* mapDocument)
{
    // TODO clean/reset ?

    if (nullptr != mapDocument) {
        auto map(mapDocument->m_map);
        m_ui->lineEditMapName->setText(mapDocument->m_mapName);
        m_ui->lineEditChipset->setText(QString::fromStdString(map->chipset()));
        m_ui->lineEditMusic->setText(QString::fromStdString(map->music()));
        m_ui->spinBoxMapHeight->setValue(map->height());
        m_ui->spinBoxMapWidth->setValue(map->width());
    }

    // TODO replace call to filesystem with QFile ?
    m_chipsetPath = QString::fromStdString((project.coreProject().projectPath() / "chipsets").string());

    // On Windows, fs::pash puts some backslashes. That sucks.
    // Clean path uses slashes, remove weird paths as "folder/../folder"
    m_chipsetPath = QDir::cleanPath(m_chipsetPath);
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

bool MapEditDialog::inputsAreValid(QString* errorMessage)
{
    if (m_ui->lineEditMapName->text().isEmpty()) {
        if (errorMessage != nullptr)
            *errorMessage = tr("You must enter a map name.");

        return false;

    } else if (m_ui->lineEditChipset->text().isEmpty()) {
        if (errorMessage != nullptr)
            *errorMessage = tr("You must enter a chipset filename.");

        return false;

    } else if (m_ui->spinBoxMapHeight->value() < 1) { // should not happen
        if (errorMessage != nullptr)
            *errorMessage = tr("You map's height must be above or equal to 1.");

        return false;

    } else if (m_ui->spinBoxMapWidth->value() < 1) { // should not happen
        if (errorMessage != nullptr)
            *errorMessage = tr("You map's width must be above or equal to 1.");

        return false;
    }
    return true;
}

void MapEditDialog::on_pushButtonBrowseChipset_clicked()
{
    // TODO use .open() instead of .exec() ?
    QFileDialog dlg(this, tr("Choose the chipset file for your map."), m_chipsetPath, "PNG files (*.png)");

    if (dlg.exec() != QDialog::Accepted)
        return;

    // If user has selected several files, we only use the first one
    QString selectedChipset     = dlg.selectedFiles().at(0);
    int indexOfFileNameInString = selectedChipset.indexOf(m_chipsetPath);
    if (indexOfFileNameInString < 0) {
        QMessageBox::critical(this, tr("Error"), tr("Please select a chipset inside the 'chipset' folder."));
    } else {
        m_ui->lineEditChipset->setText(selectedChipset.mid(indexOfFileNameInString + 1 + m_chipsetPath.size()));
    }
}

void MapEditDialog::on_pushButtonOK_clicked()
{
    QString errorMessage;
    if (inputsAreValid(&errorMessage)) {
        accept();
    } else {
        QMessageBox::critical(this, tr("Error"), errorMessage);
    }
}

void MapEditDialog::on_pushButtonCancel_clicked()
{
    reject();
}
