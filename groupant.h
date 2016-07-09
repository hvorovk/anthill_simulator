/*
 * Класс группы рабочих муравьев
*/
#ifndef GROUPANT_H
#define GROUPANT_H
#include "ant.h"

enum Type{
    //Тип рабочего
    Forager = 0,
    Solider,
    Nanny
};

class GroupAnt:public Ant
{
private:
    constexpr static int MAX_AGE = 24, BASE_HP = 0.1, REGEN = 0.1, MAX_RES = 5;
    int countOfAnts;
    bool where;
    Type type;
    int maxResource;
public:
    int getRes(){return maxResource;}
    QString toString();
    QString getName(){return name;}
    void setWhere(bool a){where = a;}
    bool onAntHill(){return where;}
    GroupAnt(QString name, Type type);
    Type getType(){return type;}
    bool checkAge();
};

#endif // GROUPANT_H
