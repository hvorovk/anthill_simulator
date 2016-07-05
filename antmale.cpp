#include "antmale.h"

AntMale::AntMale()
{
    sex = true;
    age = 0;
    health.first = health.second = MAX_AGE;
    heathRecoveryOnStep = REGEN;
    life = true;
}

bool AntMale::checkAge(){
    if(age>=MAX_AGE) return false;
    return true;
}
