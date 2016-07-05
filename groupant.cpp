#include "groupant.h"

GroupAnt::GroupAnt(QString n,Type type){
    age = 0;
    health.first = health.second = MAX_AGE;
    heathRecoveryOnStep = REGEN;
    name = n;
    life = true;
    this->type = type;
}

bool GroupAnt::checkAge(){
    if(age>=MAX_AGE) return false;
    return true;
}
