#ifndef ANTHILL_H
/*
 * Класс муравейника
*/
#define ANTHILL_H
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QtCore>
#include <antqueen.h>
#include <groupant.h>
#include <sectordialog.h>

class MapItemAH: public QGraphicsEllipseItem{
private:
    SectorDialog *dialog;
public:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    MapItemAH():QGraphicsEllipseItem(){
    }
    MapItemAH(int x,int y,int w,int h, QColor a = Qt::red):QGraphicsEllipseItem(x,y,w,h){
        setAcceptHoverEvents(true);
        setOpacity(0.6);
        setBrush(*new QBrush(a));
    }
};


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
    QVector<TypeOfSector> map;
    QVector<QPair<Ant*,int> > antLocation;
    int sectorCount;
    MapOfAntHill(AntQueen *a,GroupAnt *b){
        sectorCount = 2;
        map.append(QUEEN);
        map.append(POSTERITY);
        antLocation.append(QPair<Ant*,int>(a,0));
        antLocation.append(QPair<Ant*,int>(b,1));
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
    int storeAll, level;
    QPair<double,double>  health;
    double armor;
    MapOfAntHill *mapAntHill;
    QVector<GroupAnt*> freeAnts;
public:
    AntHill(QString);
    QGraphicsScene* getScene(){
        return scene;
    }
    bool addSector(TypeOfSector type);

    int attack(int);

    int armorEffect(int attack){
        return (attack*sqrt(armor*10))/100;
    }

    void nextStep();

};

#endif // ANTHILL_H
