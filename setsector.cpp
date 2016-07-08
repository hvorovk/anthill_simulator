#include "setsector.h"
#include "ui_setsector.h"

SetSector::SetSector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetSector)
{
    ui->setupUi(this);
}

SetSector::~SetSector()
{
    delete ui;
}
