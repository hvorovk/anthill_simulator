#include "setsector.h"
#include "ui_setsector.h"

SetSector::SetSector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetSector)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(alpha()));
}

void SetSector::get(QVector<GroupAnt *> free,int pos,GroupAnt *curr){
    ui->comboBox->clear();
    if(curr != nullptr) ui->comboBox->addItem(curr->getName());
    else ui->comboBox->addItem("Пусто");
    foreach (auto i, free) {
        if(i->getType() == Type::Forager){
            ui->comboBox->addItem(i->getName());
            this->free.append(i);
        }
    }
    ui->comboBox->setCurrentIndex(0);
    this->pos = pos;
}
void SetSector::alpha(){
    if(ui->comboBox->currentIndex() == 0);
    else emit set(free[ui->comboBox->currentIndex()-1],pos);
    free.clear();
}

SetSector::~SetSector()
{
    delete ui;
}
