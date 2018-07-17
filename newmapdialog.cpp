#include "newmapdialog.h"
#include "ui_newmapdialog.h"

NewMapDialog::NewMapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewMapDialog)
{
    ui->setupUi(this);
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
