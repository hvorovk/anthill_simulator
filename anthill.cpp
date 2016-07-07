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
    mapAntHill = new MapOfAntHill(queen,ants[1]);
    scene->addPixmap(QPixmap(":/img/data/img/sceneback.jpg"));
    auto a = new MapItemAH(0,0,50,50);
    scene->addItem(a);
}

bool AntHill::addSector(TypeOfSector type){
    if(mapAntHill->sectorCount == MAP_SIZE_H * MAP_SIZE_W) return false;
    mapAntHill->map.append(type);
    mapAntHill->sectorCount += 1;
    return true;
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
        setBrush(*new QBrush(*new QColor(200,0,0)));
        dialog = new SectorDialog();
        dialog->show();
    }
}

void MapItemAH::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    setBrush(*new QBrush(*new QColor(255,0,0)));
}

void MapItemAH::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
   setOpacity(0.9);
}

void MapItemAH::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
   setOpacity(0.4);
}

void MapItemAH::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){

}
