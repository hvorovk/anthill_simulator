/*
 * Класс королевы
*/
#ifndef ANTQUEEN_H
#define ANTQUEEN_H
#include "ant.h"

class AntQueen : public Ant
{
private:
    constexpr static int MAX_AGE = 144, BASE_HP = 20, REGEN = 0.1;
    int productivityOnStep,level;
public:
    bool checkAge();
    int getProduct(){return productivityOnStep;}
    int getLevel(){return level;}
    QString toString();
    AntQueen(QString name);
};

#endif // ANTQUEEN_H
