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
