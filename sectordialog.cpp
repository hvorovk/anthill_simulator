#include "sectordialog.h"
#include "ui_sectordialog.h"

SectorDialog::SectorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SectorDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(sigS()));
}

SectorDialog::~SectorDialog()
{
    delete ui;
}

void SectorDialog::sigS(){
    QString a = ui->comboBox->currentText();
    if(a == "Хранилище") sig(TypeOfSector::STORAGE,b);
    else if(a == "Защита") sig(TypeOfSector::DEFENSE,b);
    else sig(TypeOfSector::POSTERITY,b);
}
