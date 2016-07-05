/*
 * Класс мира
*/
#ifndef WORLD_H
#define WORLD_H
#include "anthill.h"


struct SectorCharacteristic{
    double chanceOfAccidents, chanceToAttack, mortality,
    productivity, fertility;
};

struct MapOfWorld{
    QVector <QVector<SectorCharacteristic> >charactOfSectors;
    QVector <QPair<int,GroupAnt*> > busyOfAnt;
    int antHillLocate;
};

class World
{
private:
    int currentStep;
    QGraphicsScene *scene;
    AntHill *antHill;
    MapOfWorld *map;
public:
    const AntHill* getAntHill(){
        return antHill;
    }
    int getStep(){return currentStep;}
    void nextStep();
    World();
};

#endif // WORLD_H
