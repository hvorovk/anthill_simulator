#include "anthill.h"

AntHill::AntHill(QString n){
    name = n;
    health.first = health.second = BASE_HP;
    scene = new QGraphicsScene();
    queen = new AntQueen("Элеонора");
    ants.append(new GroupAnt("1",Forager));
    ants.append(new GroupAnt("2",Nanny));
    storeAll = BASE_STORAGE;
    storeFood.first = storeMaterials.first = storeWater.first = BASE_STORAGE/3;
    storeFood.second = storeMaterials.second = storeWater.second = 5;
    level = 1;
    armor = 1;
    freeAnts.append(ants[0]);
    map = new MapOfAntHill(queen,ants[1]);
    scene->addPixmap(QPixmap(":/img/data/img/sceneback.jpg"));
    foreach (auto a, map->items) {
        scene->addItem(a);
    }
}

void AntHill::addSector(TypeOfSector type, int p){
    storeMaterials.second -=5;
    map->map[p] = type;
    map->items[p]->setBusy(true);
    map->items[p]->setColor(type);
    map->sectorCount += 1;
}

int AntHill::attack(int attack){
   health.second -= attack - armorEffect(attack);
   int attackReturn = queen->getAttack() ;
   foreach (GroupAnt* i, ants) {
       if(i->onAntHill()) attackReturn +=i->getAttack();
   }
   return attackReturn;
}

void AntHill::nextStep(){

}

void MapItemAH::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::LeftButton){
       if(alpha == Qt::white) setBrush(*new QBrush(Qt::gray));
       else if(alpha == Qt::yellow) setBrush(*new QBrush(QColor(150,150,0)));
       else if(alpha == Qt::blue) setBrush(*new QBrush(QColor(0,0,150)));
       else if(alpha == Qt::green) setBrush(*new QBrush(QColor(0,150,0)));
       else setBrush(*new QBrush(QColor(150,0,0)));
    }
}

void MapItemAH::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    setBrush(*new QBrush(alpha));
    emit clicked(id);
}

void MapItemAH::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
   setOpacity(0.9);
}

void MapItemAH::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
   setOpacity(0.4);
}

void MapItemAH::setColor(TypeOfSector a){
    if(a == QUEEN) alpha = Qt::yellow;
    else if(a == POSTERITY) alpha = Qt::green;
    else if(a == STORAGE) alpha = Qt::blue;
    else alpha = Qt::red;
    setBrush(*new QBrush(alpha));
}
