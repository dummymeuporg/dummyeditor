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
