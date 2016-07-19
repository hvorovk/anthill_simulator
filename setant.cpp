#include "setant.h"
#include "ui_setant.h"

setAnt::setAnt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setAnt)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(alpha()));
}
void setAnt::get(QVector<GroupAnt*> all, int pos, GroupAnt* cur, TypeOfSector type){
    ui->comboBox->clear();
    if(cur == nullptr) ui->comboBox->addItem("Пусто");
    else ui->comboBox->addItem(cur->getName());
    this->pos = pos;
    Type temp;
    if(type == TypeOfSector::POSTERITY) temp = Type::Nanny;
    else if(type == TypeOfSector::DEFENSE) temp = Type::Solider;
    foreach (GroupAnt* i, all) {
        if(i->getType() == temp){
            ant.append(i);
            ui->comboBox->addItem(i->getName());
        }
    }
}

void setAnt::alpha(){
    if(ui->comboBox->currentIndex() != 0){
        emit sig(ant[ui->comboBox->currentIndex()-1],pos);
    }
}

setAnt::~setAnt()
{
    delete ui;
}
void setAnt::clear(){
    ant.clear();
    ui->comboBox->clear();
}
