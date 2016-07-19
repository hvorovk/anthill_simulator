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

enum class TypeOfSector{
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
    rem(int a);
    change(int i);
protected:
    int id;
    QColor color;
    bool busy;
public:
    MapItemAH():QGraphicsEllipseItem(){
    }

    MapItemAH(int x,int y,int w,int h, int i = 0, QColor a = Qt::white):QGraphicsEllipseItem(x,y,w,h){
        setAcceptHoverEvents(true);
        busy = false;
        color = a;
        setOpacity(0.6);
        setBrush(*new QBrush(a));
        id = i;
    }

    void setBusy(bool b){
        busy = b;
    }

    bool onBusy(){return busy;}

    void setColor(TypeOfSector);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};

struct MapOfAntHill{
    //Карта муравейника
    QVector<TypeOfSector> map;
    QVector<GroupAnt*> antLocation;
    QVector<MapItemAH*> items;
    int sectorCount;

    MapOfAntHill(GroupAnt *b){
        sectorCount = 2;
        for(int i = 0; i < MAP_SIZE_H; i++){
            for(int j = 0; j < MAP_SIZE_W; j++){
                items.append(new MapItemAH(50*j, 50*i,50,50,i*12+j));
                map.append(TypeOfSector::NONE);
                antLocation.append(nullptr);
            }
        }
        antLocation[1] = b;
        map[0] = TypeOfSector::QUEEN;
        map[1] = TypeOfSector::POSTERITY;
        items[0]->setBusy(true); items[1]->setBusy(true);
        items[0]->setColor(map[0]); items[1]->setColor(map[1]);
    }
};

class AntHill
{
private:
    constexpr static int BASE_HP = 100, BASE_STORAGE = 150;
    int reproduct, countActivePosterity;
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
    int getCount(){return map->sectorCount;}
    void addStore(int f, int w, int m){
        storeFood.second += f;
        storeWater.second += w;
        storeMaterials.second += m;
        if(storeFood.second>storeFood.first) storeFood.second = storeFood.first;
        if(storeWater.second>storeWater.first) storeWater.second = storeWater.first;
        if(storeMaterials.second>storeMaterials.first) storeMaterials.second = storeMaterials.first;
    }

    void addFree(GroupAnt* a){
        //Добавить к свободным
        freeAnts.append(a);
    }

    void remFree(GroupAnt *a){
        //Удалить из свободных муравья
        freeAnts.removeOne(a);
    }

    void setAnt(GroupAnt *a, int pos){
        //Поставить муравья на внутреннюю ячейку муравейника
        remFree(a);
        if(map->antLocation[pos] == nullptr) map->antLocation[pos] = a;
        else{
            addFree(map->antLocation[pos]);
            map->antLocation[pos] = a;
            if(a->getType() == Type::Nanny) countActivePosterity -= 1;
        }
        if(a->getType() == Type::Nanny) countActivePosterity += 1;
    }

    QString toString();
    QString getTextSector(int i);
    AntHill(QString);
    void nextStep();
    void addSector(TypeOfSector type, int p);
    int attack(int);
    void repr(Type);

    int getRepr(){return reproduct;}
    GroupAnt* getAnt(int pos){return map->antLocation[pos];}
    TypeOfSector getType(int pos){return map->map[pos];}
    QVector<GroupAnt*> getFree(){ return freeAnts;}
    QPair<int,int> getWater(){return storeWater;}
    QPair<int,int> getFood(){return storeFood;}
    QPair<int,int> getMater(){return storeMaterials;}
    QGraphicsScene* getScene(){return scene;}
    QVector<MapItemAH*> getButtons(){return map->items;}
    int armorEffect(int attack){return (attack*sqrt(armor*10))/100;}
};

#endif // ANTHILL_H
