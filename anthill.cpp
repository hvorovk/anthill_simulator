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
    poster = 1;
    map = new MapOfAntHill(ants[1]);
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

QString AntHill::getTextSector(int i){
    QString out;
    out += "Ячейка " + QString::number(i) + "\n";
    if(map->map[i] == QUEEN)
        out += "Это ячейка королевы\n" + queen->toString();
    else if(map->map[i] == STORAGE)
        out += "Это хранилище,\n повышает общую\nвместимость на\n15 единиц";
    else if(map->map[i] == DEFENSE){
        GroupAnt *a = nullptr;
        for(int j = 0; j < map->antLocation.length();j++){
           if(map->antLocation[j].second == i){
               a = map->antLocation[j].first;
           }
        }
        out += "Это клетка солдат";
        if(a == nullptr) out += "\nЗдесь ни  кого нет.";
        else out += "\n+1 к защите\n" + a->toString();
    }
    else if(map->map[i] == POSTERITY){
        GroupAnt *a = nullptr;
        out += "Это клетка родильни\n";
        for(int j = 0; j < map->antLocation.length();j++){
           if(map->antLocation[j].second == i){
               a = map->antLocation[j].first;
           }
        }
        if(a!=nullptr) out += a->toString();
    }
    else
        out += "Эта клетка пуста,\nдля приобретения\nнажмите левой\nкнопкой мыши.";
    return out;
}

QString AntHill::toString(){
    QString out;
    out += "Название: " + name;
    out += "\nКоролева: " + queen->getName();
    out += "\nСвободных рабочих: " + QString::number(freeAnts.length());
    out += "\nПрочность: " + QString::number(health.second) + "/" + QString::number(health.first);
    out += "\nУровень: " + QString::number(level);
    return out;
}


void AntHill::nextStep(){

}

void MapItemAH::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::LeftButton){
       if(color == Qt::white) setBrush(*new QBrush(Qt::gray));
       else if(color == Qt::yellow) setBrush(*new QBrush(QColor(150,150,0)));
       else if(color == Qt::blue) setBrush(*new QBrush(QColor(0,0,150)));
       else if(color == Qt::green) setBrush(*new QBrush(QColor(0,150,0)));
       else setBrush(*new QBrush(QColor(150,0,0)));
    }
}

void MapItemAH::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    setBrush(*new QBrush(color));
    emit clicked(id);
}

void MapItemAH::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
   setOpacity(0.9);
   emit enter(id);
}

void MapItemAH::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
   setOpacity(0.6);
   emit leave();
}

void MapItemAH::setColor(TypeOfSector a){
    if(a == QUEEN) color = Qt::yellow;
    else if(a == POSTERITY) color = Qt::green;
    else if(a == STORAGE) color = Qt::blue;
    else color = Qt::red;
    setBrush(*new QBrush(color));
}
