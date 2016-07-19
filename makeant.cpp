#include "makeant.h"
#include "ui_makeant.h"

MakeAnt::MakeAnt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MakeAnt)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(alpha()));
    ui->comboBox->addItem("Фуражир");
    ui->comboBox->addItem("Няня");
    ui->comboBox->addItem("Солдат");
}

void MakeAnt::alpha(){
    switch(ui->comboBox->currentIndex()){
    case 0:
        emit sig(Type::Forager);
        break;
    case 1:
        emit sig(Type::Nanny);
        break;
    case 2:
        emit sig(Type::Solider);
    }
}

MakeAnt::~MakeAnt()
{
    delete ui;
}
