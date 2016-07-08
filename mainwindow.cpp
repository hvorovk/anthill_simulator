#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Инициализация полей
    alpha = new menu();
    //Установка связей
    connect(alpha,SIGNAL(loadSig()),this,SLOT(loadS()));
    connect(alpha,SIGNAL(saveSig()),this,SLOT(saveS()));
    connect(alpha,SIGNAL(newSig()),this,SLOT(newS()));
    connect(alpha,SIGNAL(loadSig()),this,SLOT(loadS()));
    connect(alpha,SIGNAL(overSig()),this,SLOT(overS()));
    connect(alpha,SIGNAL(exitSig()),this,SLOT(exitS()));
    connect(alpha,SIGNAL(closed()),this,SLOT(closeMenu()));

    connect(ui->menu,SIGNAL(clicked()),this,SLOT(openMenu()));
    connect(ui->step,SIGNAL(clicked()),this,SLOT(nextStep()));
    connect(ui->viewMode,SIGNAL(clicked()),this,SLOT(changeViewMode()));

    clearStore();
    disableButtons();
}

void MainWindow::loadS(){
    //Загрузка сессии
    enableButtons();
}

void MainWindow::saveS(){
    //Сохранение сессии

}

void MainWindow::nextStep(){
    //Новый шаг симуляции
    antHill->nextStep();
}

void MainWindow::exitS(){
    //Завершение всей программы
    exit(0);
}

void MainWindow::addSectAH(int a,int b){
    switch (a) {
    case 0:
        antHill->addSector(STORAGE,b);
        break;
    case 1:
        antHill->addSector(POSTERITY,b);
        break;
    case 2:
        antHill->addSector(DEFENSE,b);
    }
    refreshStore();
}

void MainWindow::newS(){
    //Новая сессия
    antHill = new AntHill("anthill");
    world = new World(antHill);
    add = new SectorDialog();
    foreach (auto a, antHill->getButtons()) {
        connect(a,SIGNAL(clicked(int)),this,SLOT(sectorAntHill(int)));
        connect(a,SIGNAL(enter(int)),this,SLOT(enterAH(int)));
        connect(a,SIGNAL(leave()),this,SLOT(leaveAH()));
    }
    foreach (auto a, world->getButtons()) {
        //connect(a,SIGNAL(clicked(int)),this,SLOT(sectorAntHill(int)));
        connect(a,SIGNAL(enter(int)),this,SLOT(enterW(int)));
        connect(a,SIGNAL(leave()),this,SLOT(leaveW()));
    }
    connect(add,SIGNAL(sig(int,int)),this,SLOT(addSectAH(int,int)));
    ui->generalScene->setScene(antHill->getScene());
    enableButtons();
    refreshStore();
}

void MainWindow::overS(){
    disableButtons();
    ui->generalScene->setScene(new QGraphicsScene());
    foreach (auto a, antHill->getButtons()) {
        disconnect(a,SIGNAL(clicked(int)),this,SLOT(sectorAntHill(int)));
    }
    disconnect(add,SIGNAL(sig(int,int)),this,SLOT(addSectAH(int,int)));
    delete antHill;
    delete world;
    delete add;
    clearStore();
    ui->info->clear();
}

void MainWindow::openMenu(){
    //Открыть меню и скрыть основное окно
    alpha->show();
    this->hide();
}

void MainWindow::closeMenu(){
    //Открыть основное окно в случае закрытия основного меню
    this->show();
}

void MainWindow::clearStore(){
    ui->food->setText("Пища: NaN");
    ui->water->setText("Вода: NaN");
    ui->mater->setText("Материалы: NaN");
}


void MainWindow::sectorAntHill(int a){
    if(antHill->getButtons()[a]->onBusy()){

    }else if(antHill->getMat()>=5){
        add->add(a);
        add->show();
    }else{
        (new QMessageBox(QMessageBox::Warning,"Нет ресурсов","Не хватает " +
                         QString::number(5-antHill->getMat())+
                         " ресурсов на постройку ячейки муравейника."))->show();
    }
}

void MainWindow::changeViewMode(){
    //Изменение отображения graphicsview
    //Режим просмотра муравейника или мира.
    if(ui->generalScene->scene() == antHill->getScene())
        ui->generalScene->setScene(world->getScene());
    else ui->generalScene->setScene(antHill->getScene());
}

void MainWindow::enableButtons(){
    //Включение основных кнопок управления на основной форме
    ui->step->setEnabled(true);
    ui->viewMode->setEnabled(true);
}

void MainWindow::disableButtons(){
    //Отключение основных кнопок управния на основной форме
    ui->step->setDisabled(true);
    ui->viewMode->setDisabled(true);
}

void MainWindow::refreshStore(){
    ui->food->setText("Пища: " + QString::number(antHill->getFood().second) +
                      "/" + QString::number(antHill->getFood().first));
    ui->water->setText("Вода: " + QString::number(antHill->getWater().second) +
                      "/" + QString::number(antHill->getWater().first));
    ui->mater->setText("Материалы: " + QString::number(antHill->getMater().second) +
                      "/" + QString::number(antHill->getMater().first));
}
void MainWindow::leaveW(){
    ui->info->clear();
}

void MainWindow::enterW(int a){
    ui->info->setText(world->getTextSector(a));
}

void MainWindow::enterAH(int a){
    ui->info->setText(antHill->getTextSector(a));
}

void MainWindow::leaveAH(){
    ui->info->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}
