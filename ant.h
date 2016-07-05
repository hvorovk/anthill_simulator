/*
 * Абстрактный класс муравей
*/
#ifndef ANT_H
#define ANT_H
#include <QtCore>

class Ant
{
protected:
    QString name;
    int age, attack;
    bool sex, life;
    QPair<double,double> health;
    double heathRecoveryOnStep;
public:
    int attacked(int count){
        //Метот отображающий нападение
        //Наносим урон, если фатально то говорим об этом и
        //Возвращаем ответный урон
        health.second -= count;
        if(health.second<=0) kill("Убит");
        return attack;
    }

    int getAttack(){
        return attack;
    }

    QPair<double,double> getHealth(){
        return health;
    }

    void recoveryHealthOnStep(){
        //Восстановление хп
        health.second += heathRecoveryOnStep;
        if(health.second > health.first) health.second = health.first;
    }

    QString getName(){
        return name;
    }

    int getAge(){
        return age;
    }

    void incAge(){
        //Увеличение количества прожитых шагов
        age++;
        if(!checkAge()){
            sex?kill("Умер от старости."):kill("Умерла от старости.");
        }
    }
    bool alive(){return life;}

    void kill(QString reason){
        //Метод вызываемый при смерти
        qDebug()<<reason;
        life = false;
    }

    virtual bool checkAge()=0;
};

#endif // ANT_H
