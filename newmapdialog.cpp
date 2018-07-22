#include "newmapdialog.h"
#include "ui_newmapdialog.h"

#include "dummy/map.h"

NewMapDialog::NewMapDialog(QWidget *parent,
                           const Dummy::Map* map) :
    QDialog(parent),
    ui(new Ui::NewMapDialog)
{
    ui->setupUi(this);

    if (nullptr != map) {
        ui->lineEditMapName->setText(map->name());
        ui->lineEditChipset->setText(map->chipset());
        ui->lineEditMusic->setText(map->music());
        ui->spinBoxMapHeight->setValue(map->height());
        ui->spinBoxMapWidth->setValue(map->width());
    }
}

NewMapDialog::~NewMapDialog()
{
    delete ui;
}

QString NewMapDialog::getMapName() const {
    return ui->lineEditMapName->text();
}

quint16 NewMapDialog::getWidth() const {
    return ui->spinBoxMapWidth->value();
}

quint16 NewMapDialog::getHeight() const {
    return ui->spinBoxMapHeight->value();
}

QString NewMapDialog::getChipset() const {
    return ui->lineEditChipset->text();
}

QString NewMapDialog::getMusic() const {
    return ui->lineEditMusic->text();
}
