#ifndef ANTHILL_H
/*
 * Класс муравейника
*/
#define ANTHILL_H
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QtCore>
#include <antqueen.h>
#include <groupant.h>
#include <sectordialog.h>

enum TypeOfSector{
    //Типы секторов
    STORAGE = 0,
    POSTERITY = 1,
    QUEEN = 2,
    DEFENSE = 3,
    NONE
};

const int MAP_SIZE_W = 12, MAP_SIZE_H = 8, COST_SECTOR = 5;

class MapItemAH:public QObject, public QGraphicsEllipseItem{
    Q_OBJECT
    /*
     * Если ячейка белая то она свободна, если хранилище то синяя,
     * если родильня то зеленая, защита красная, королева желтая
    */
signals:
    //передает позицию
    clicked(int p);
    enter(int);
    leave();
protected:
    int id;
    QColor color;
    bool busy;
public:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    MapItemAH():QGraphicsEllipseItem(){
    }

    void setColor(TypeOfSector);

    void setBusy(bool b){
        busy = b;
    }

    bool onBusy(){return busy;}

    MapItemAH(int x,int y,int w,int h, int i = 0, QColor a = Qt::white):QGraphicsEllipseItem(x,y,w,h){
        setAcceptHoverEvents(true);
        busy = false;
        color = a;
        setOpacity(0.6);
        setBrush(*new QBrush(a));
        id = i;
    }
};

struct MapOfAntHill{
    //Карта муравейника
    QVector<TypeOfSector> map;
    QVector<QPair<GroupAnt*,int> > antLocation;
    QVector<MapItemAH*> items;
    int sectorCount;

    MapOfAntHill(GroupAnt *b){
        sectorCount = 2;

        antLocation.append(QPair<GroupAnt*,int>(b,1));
        for(int i = 0; i < MAP_SIZE_H; i++){
            for(int j = 0; j < MAP_SIZE_W; j++){
                items.append(new MapItemAH(50*j, 50*i,50,50,i*12+j));
                map.append(NONE);
            }
        }
        map[0] = QUEEN;
        map[1] = POSTERITY;
        items[0]->setBusy(true); items[1]->setBusy(true);
        items[0]->setColor(map[0]); items[1]->setColor(map[1]);
    }
};

class AntHill
{
private:
    constexpr static int BASE_HP = 100, BASE_STORAGE = 150;
    QGraphicsScene *scene;
    QString name;
    AntQueen *queen;
    QVector<GroupAnt*> ants;
    QPair<int,int> storeWater, storeFood, storeMaterials;
    int storeAll, level, poster;
    QPair<double,double>  health;
    double armor;
    MapOfAntHill *map;
    QVector<GroupAnt*> freeAnts;
public:
    QString toString();
    QString getTextSector(int i);
    AntHill(QString);
    QPair<int,int> getWater(){
        return storeWater;
    }
    QPair<int,int> getFood(){
        return storeFood;
    }
    QPair<int,int> getMater(){
        return storeMaterials;
    }

    QGraphicsScene* getScene(){
        return scene;
    }
    QVector<MapItemAH*> getButtons(){return map->items;}
    void addSector(TypeOfSector type, int p);

    int attack(int);

    int getMat(){ return storeMaterials.second;}

    int armorEffect(int attack){
        return (attack*sqrt(armor*10))/100;
    }

    void nextStep();

};

#endif // ANTHILL_H
