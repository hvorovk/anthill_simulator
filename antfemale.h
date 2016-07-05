/*
 * Класс крылатой самки
*/
#ifndef ANTFEMALE_H
#define ANTFEMALE_H
#include "ant.h"

class AntFemale : public Ant
{
private:
    constexpr static int MAX_AGE = 36, BASE_HP = 1, REGEN = 0.05;
public:
    AntFemale();
    bool checkAge();
};

#endif // ANTFEMALE_H
