#include "mapeditdialog.h"
#include "ui_mapeditdialog.h"

#include "dummy/map.h"

MapEditDialog::MapEditDialog(std::shared_ptr<const Dummy::Map> map,
                             QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapEditDialog)
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
