#ifndef ANTHILL_H
/*
 * Класс муравейника
*/
#define ANTHILL_H
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QtCore>
#include <antqueen.h>
#include <groupant.h>
const int MAP_SIZE_W = 11, MAP_SIZE_H = 7;

enum TypeOfSector{
    //Типы секторов
    STORAGE = 0,
    POSTERITY = 1,
    QUEEN = 2,
    DEFENSE = 3
};

struct MapOfAntHill{
    //Карта муравейника
    QVector<QVector<TypeOfSector> > map;
    QVector<QPair<Ant*,int> > antLocation;
    int sectorCount;
};

class AntHill
{
private:
    constexpr static int BASE_HP = 100;
    QGraphicsScene *scene;
    QString name;
    AntQueen *queen;
    QVector<GroupAnt*> ants;
    QPair<int,int> storeWater, storeFood, storeMaterials;
    int storeAll, level;
    QPair<double,double>  health;
    double armor;
    MapOfAntHill *mapAntHill;
    QVector<GroupAnt*> freeAnts;
public:
    AntHill();
    QGraphicsScene* getScene(){
        return scene;
    }
    bool addSector();
    void attack(int);

    void nextStep();

};

#endif // ANTHILL_H
