#include "antfemale.h"

AntFemale::AntFemale()
{
    sex = false;
    age = 0;
    health.first = health.second = MAX_AGE;
    heathRecoveryOnStep = REGEN;
    life = true;
}

bool AntFemale::checkAge(){
    if(age>=MAX_AGE) return false;
    return true;
}
