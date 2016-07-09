/*
 * Класс мира
*/
#ifndef WORLD_H
#define WORLD_H

#include "anthill.h"

class MapItemW:public MapItemAH{
public:
    MapItemW(int x,int y,int w,int h, int id = 0, QColor a = Qt::white):
        MapItemAH(x,y,w,h,id,a){}
    void setColor(int a){
        // Если 0 то белый(пусто), если 1 то синий(муравей), если 2 то зеленый(муравейник)
        switch (a) {
        case 0:
            color = Qt::white;
            break;
        case 1:
            color = Qt::blue;
            break;
        case 2:
            color = Qt::green;
            break;
        }
        setBrush(*new QBrush(color));
    }
    int getType(){
        if(color == Qt::white) return 0;
        else if(color == Qt::blue) return 1;
        else return 2;
    }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
        setBrush(*new QBrush(color));
        if(event->button() == Qt::LeftButton && color != Qt::green) emit clicked(id);
    }

    void mousePressEvent(QGraphicsSceneMouseEvent *event){
        if(color == Qt::white) setBrush(*new QBrush(Qt::gray));
        else if(color == Qt::blue) setBrush(*new QBrush(QColor(0,0,150)));
        else if(color == Qt::green) setBrush(*new QBrush(QColor(0,150,0)));
        if(event->button() == Qt::RightButton && color != Qt::green){
            emit rem(id);
        }
    }
};

struct SectorCharacteristic{
    double chanceOfAccidents, chanceToAttack, fertility;
    QString toString(){
        return "Шанс аварии: " + QString::number(chanceOfAccidents) +
                "\nШанс атаки: " + QString::number(chanceToAttack) +
                "\nПлодородность: " +  QString::number(fertility) + "\n";
    }
};

struct MapOfWorld{
    QVector<MapItemW*> items;
    QVector<SectorCharacteristic*>charactOfSectors;
    QVector<GroupAnt*> busyOfAnt;
    int antHillLocate;
    MapOfWorld(){
        for(int i = 0; i < MAP_SIZE_H; i++){
            for(int j = 0; j < MAP_SIZE_W; j++){
                items.append(new MapItemW(50*j, 50*i,50,50,i*12+j));
                auto a = new SectorCharacteristic();
                a->chanceOfAccidents = (rand()%100)/100.0;
                a->chanceToAttack = (rand()%100)/100.0;
                a->fertility = ((rand()%50)+50)/100.0;
                charactOfSectors.append(a);
                busyOfAnt.append(nullptr);
            }
        }
        antHillLocate = 0;
        items[0]->setColor(2);
    }
};

class World
{
private:
    int currentStep;
    QGraphicsScene *scene;
    AntHill *antHill;
    MapOfWorld *map;
public:
    GroupAnt* getAnt(int i){return map->busyOfAnt[i];}
    void remove(GroupAnt*);
    void add(GroupAnt*, int p);
    QString getTextSector(int);
    QGraphicsScene* getScene(){return scene;}
    QVector<MapItemW*> getButtons(){return map->items;}
    int getStep(){return currentStep;}
    void nextStep();
    World(AntHill*);
};

#endif // WORLD_H
