#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>

#include "mapeditdialog.hpp"
#include "ui_mapeditdialog.h"

#include "editormap.hpp"

MapEditDialog::MapEditDialog(
    const std::shared_ptr<const EditorProject> project,
    std::shared_ptr<Misc::MapDocument> mapDocument,
    QWidget *parent) : QDialog(parent),
                       ui(new Ui::MapEditDialog),
                       m_project(project)
{
    ui->setupUi(this);
    auto map(mapDocument->map());
    if (nullptr != map) {
        ui->lineEditMapName->setText(mapDocument->mapName());
        ui->lineEditChipset->setText(QString(map->chipset().c_str()));
        ui->lineEditMusic->setText(QString(map->music().c_str()));
        ui->spinBoxMapHeight->setValue(map->height());
        ui->spinBoxMapWidth->setValue(map->width());
    }
}

MapEditDialog::~MapEditDialog()
{
    delete ui;
}

QString MapEditDialog::getMapName() const {
    return ui->lineEditMapName->text();
}

quint16 MapEditDialog::getWidth() const {
    return ui->spinBoxMapWidth->value();
}

quint16 MapEditDialog::getHeight() const {
    return ui->spinBoxMapHeight->value();
}

QString MapEditDialog::getChipset() const {
    return ui->lineEditChipset->text();
}

QString MapEditDialog::getMusic() const {
    return ui->lineEditMusic->text();
}

void MapEditDialog::onChipsetBrowse() {
    QString chipsetPath(
        (m_project->coreProject().projectPath() / "chipsets").string().c_str()
    );
    QFileDialog dlg(this, tr("Choose the chipset file for your map."),
                    chipsetPath, "PNG files (*.png)");
    dlg.exec();

    if(dlg.result() == QDialog::Accepted) {
        int index;
        QStringList selectedFiles = dlg.selectedFiles();
        QString selectedChipset = selectedFiles.at(0);
        if((index = selectedChipset.indexOf(chipsetPath)) < 0) {
            QMessageBox::critical(
                this,
                tr("Error"),
                tr("Please select a chipset inside the 'chipset' folder."));
        } else {
            ui->lineEditChipset->setText(
                selectedChipset.mid(index + chipsetPath.size()));
        }
    }
}

void MapEditDialog::onOK() {
    if (ui->lineEditMapName->text() == "") {
        QMessageBox::critical(
            this,
            tr("Error"),
            tr("You must enter a map name."));
    } else if(ui->lineEditChipset->text() == "") {
        QMessageBox::critical(
            this,
            tr("Error"),
            tr("You must enter a chipset filename."));
    } else if(ui->spinBoxMapHeight->value() < 1) {
        QMessageBox::critical(
            this,
            tr("Error"),
            tr("You map's height must be above or equal to 1."));
    } else if(ui->spinBoxMapWidth->value() < 1) {
        QMessageBox::critical(
            this,
            tr("Error"),
            tr("You map's width must be above or equal to 1."));
    } else {
        accept();
    }
}
