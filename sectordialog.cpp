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
    if(a == "Хранилище") sig(0,b);
    else if(a == "Защита") sig(2,b);
    else sig(1,b);
}
