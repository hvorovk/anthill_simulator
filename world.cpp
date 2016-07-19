#include "world.h"

World::World(AntHill *alpha){
    currentStep = 0;
    scene = new QGraphicsScene();
    antHill = alpha;
    map = new MapOfWorld();
    scene->addPixmap(QPixmap(":/img/data/img/world.png"));
    foreach (auto a, map->items) {
        scene->addItem(a);
    }

}
QString World::getTextSector(int a){
    QString out = "Клетка номер " + QString::number(a) + "\n";
    if(map->items[a]->getType() == 2){
        return out + "Муравейник\n" + antHill->toString();
    }
    out +="Характеристика:\n" + map->charactOfSectors[a]->toString();
    if(map->busyOfAnt[a] == nullptr)
        return out + "Пусто";
    else
        return out + map->busyOfAnt[a]->toString();
}

void World::remove(GroupAnt* a){
    int p = map->busyOfAnt.indexOf(a);
    if(p == -1) return;
    else if(map->busyOfAnt[p] != nullptr){
        map->busyOfAnt[p] = nullptr;
        map->items[p]->setColor(0);
        antHill->addFree(a);
        map->sectorCount -= 1;
    }
}

void World::add(GroupAnt* a,int p){
    antHill->remFree(a);
    if(map->busyOfAnt[p] == nullptr){
        map->busyOfAnt[p] = a;
    }else{
        antHill->addFree(map->busyOfAnt[p]);
        map->busyOfAnt[p] = a;
    }
    map->items[p]->setColor(1);
    map->sectorCount += 1;
}

void World::nextStep(){
    antHill->nextStep();
    for(int i = 0; i<map->busyOfAnt.length();i++) {
        GroupAnt *a = map->busyOfAnt[i];
        if(a != nullptr){
            int k = a->getRes()*map->charactOfSectors[i]->fertility;
            antHill->addStore(k,k,k);
        }
    }
}
