#include "antqueen.h"

AntQueen::AntQueen(QString name)
{
    sex = false;
    productivityOnStep = 1000;
    level = 1;
    this->name = name;
    productivityOnStep = 1;
    age = 0;
    health.first = health.second = MAX_AGE;
    heathRecoveryOnStep = REGEN;
    life = true;
}

bool AntQueen::checkAge(){
    if(age>=MAX_AGE) return false;
    return true;
}

QString AntQueen::toString(){
    return "Имя: " + name +
            "\nВозраст: " + QString::number(age) +
            "\nЗдоровье: " + QString::number(health.second) +
            "/" + QString::number(health.first) +
            "\nУровень: " + QString::number(level) +
            "\nПродуктивность: "  + QString::number(productivityOnStep);
}
