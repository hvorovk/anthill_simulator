/*
 * Класс самца
*/
#ifndef ANTMALE_H
#define ANTMALE_H
#include "ant.h"

class AntMale : public Ant
{
private:
    constexpr static int MAX_AGE = 36, BASE_HP = 1, REGEN = 0.05;
public:
    AntMale();
    bool checkAge();
};

#endif // ANTMALE_H
