#include "groupant.h"

GroupAnt::GroupAnt(QString n,Type type){
    age = 0;
    health.first = health.second = MAX_AGE;
    heathRecoveryOnStep = REGEN;
    name = n;
    life = true;
    this->type = type;
    where = true;
    maxResource = MAX_RES;
    countOfAnts = 10000;
}

QString GroupAnt::toString(){
    QString a;
    if(type == Nanny) a = "няня";
    else if( type == Solider) a = "солдат";
    else a = "Фуражир\nГрузоподъемность: " + QString::number(maxResource*3);
    return "Имя: " + name +
            "\nВозраст: " + QString::number(age) +
            "\nЗдоровье: " + QString::number(health.second) +
            "/" + QString::number(health.first) +
            "\nЧисленность: " + QString::number(countOfAnts) +
            "\nСпециальность: " + a;

}

bool GroupAnt::checkAge(){
    if(age>=MAX_AGE) return false;
    return true;
}
