#include "sectordialog.h"
#include "ui_sectordialog.h"

SectorDialog::SectorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SectorDialog)
{
    ui->setupUi(this);
}

SectorDialog::~SectorDialog()
{
    delete ui;
}
