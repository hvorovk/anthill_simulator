#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <time.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Инициализация полей
    alpha = new menu();
    make = new MakeAnt();
    //Установка связей
    connect(alpha,SIGNAL(loadSig()),this,SLOT(loadS()));
    connect(alpha,SIGNAL(saveSig()),this,SLOT(saveS()));
    connect(alpha,SIGNAL(newSig()),this,SLOT(newS()));
    connect(alpha,SIGNAL(loadSig()),this,SLOT(loadS()));
    connect(alpha,SIGNAL(overSig()),this,SLOT(overS()));
    connect(alpha,SIGNAL(exitSig()),this,SLOT(exitS()));
    connect(alpha,SIGNAL(closed()),this,SLOT(closeMenu()));

    connect(ui->menu,SIGNAL(clicked()),this,SLOT(openMenu()));
    connect(ui->addAnt,SIGNAL(clicked()),make,SLOT(show()));
    connect(ui->step,SIGNAL(clicked()),this,SLOT(nextStep()));
    connect(ui->viewMode,SIGNAL(clicked()),this,SLOT(changeViewMode()));

    clearStore();
    disableButtons();
    srand(time(0));
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
    step++;
    world->nextStep();
    ui->label->setText("Шаг: " + QString::number(step));
    refreshStore();
    refreshRepr();
    ui->addAnt->setEnabled(true);

    if(world->getCount() == 96 && antHill->getCount() == 96){
        (new QMessageBox(QMessageBox::NoIcon,"Выйгрыш",
    "Вы захватили все игровое пространнство!\nЭто было очень круто!"))->show();
    }
    if(antHill->getFood().second < 0 && antHill->getWater().second > 0){
        (new QMessageBox(QMessageBox::Critical,"Проигрыш",
    "Муравейник погиб из-за голода!"))->show();
        overS();
    }
}

void MainWindow::AntMake(Type a){
    antHill->repr(a);
    refreshRepr();
    if(antHill->getRepr() == 0) ui->addAnt->setDisabled(true);
}

void MainWindow::refreshRepr(){
    ui->prod->setText("Очков воспроизводства: " + QString::number(antHill->getRepr()) +
                      "\nСвободных муравьев: " + QString::number(antHill->getFree().length()));
}

void MainWindow::exitS(){
    //Завершение всей программы
    exit(0);
}

void MainWindow::addSectAH(TypeOfSector a,int b){
    antHill->addSector(a,b);
    refreshStore();
}

void MainWindow::newS(){
    //Новая сессия
    step = 0;
    antHill = new AntHill("anthill");
    world = new World(antHill);
    add = new SectorDialog();
    addW = new SetSector();
    set = new setAnt();
    foreach (auto a, antHill->getButtons()) {
        connect(a,SIGNAL(callToChange(int)),this,SLOT(callToChange(int)));
        connect(a,SIGNAL(clicked(int)),this,SLOT(sectorAH(int)));
        connect(a,SIGNAL(enter(int)),this,SLOT(enterAH(int)));
        connect(a,SIGNAL(leave()),this,SLOT(leaveAH()));
    }
    foreach (auto a, world->getButtons()) {
        connect(a,SIGNAL(clicked(int)),this,SLOT(sectorW(int)));
        connect(a,SIGNAL(enter(int)),this,SLOT(enterW(int)));
        connect(a,SIGNAL(leave()),this,SLOT(leaveW()));
        connect(a,SIGNAL(rem(int)),this,SLOT(remove(int)));
    }
    connect(set,SIGNAL(sig(GroupAnt*,int)),this,SLOT(setAntAH(GroupAnt*,int)));
    connect(add,SIGNAL(sig(TypeOfSector,int)),this,SLOT(addSectAH(TypeOfSector,int)));
    connect(addW,SIGNAL(set(GroupAnt*,int)),this,SLOT(setAntW(GroupAnt*,int)));
    ui->generalScene->setScene(antHill->getScene());
    enableButtons();
    ui->label->setText("Шаг: 0");
    refreshStore();
    refreshRepr();
}

void MainWindow::callToChange(int i){
    set->clear();
    set->get(antHill->getFree(),i,antHill->getAnt(i),antHill->getType(i));
    set->show();
}

void MainWindow::setAntAH(GroupAnt* a, int pos){
    antHill->setAnt(a,pos);
    refreshRepr();
}

void MainWindow::remove(int i){
    world->remove(world->getAnt(i));
    refreshRepr();
}

void MainWindow::setAntW(GroupAnt* a,int b){
    world->add(a,b);
    refreshRepr();
}

void MainWindow::sectorW(int a){
    addW->get(antHill->getFree(),a,world->getAnt(a));
    addW->show();
}

void MainWindow::overS(){
    disableButtons();
    ui->generalScene->setScene(new QGraphicsScene());
    foreach (auto a, antHill->getButtons()) {
        disconnect(a,SIGNAL(callToChange(int)),this,SLOT(callToChange(int)));
        disconnect(a,SIGNAL(clicked(int)),this,SLOT(sectorAH(int)));
        disconnect(a,SIGNAL(enter(int)),this,SLOT(enterAH(int)));
        disconnect(a,SIGNAL(leave()),this,SLOT(leaveAH()));
    }
    foreach (auto a, world->getButtons()) {
        disconnect(a,SIGNAL(clicked(int)),this,SLOT(sectorW(int)));
        disconnect(a,SIGNAL(enter(int)),this,SLOT(enterW(int)));
        disconnect(a,SIGNAL(leave()),this,SLOT(leaveW()));
        disconnect(a,SIGNAL(rem(int)),this,SLOT(remove(int)));
    }
    disconnect(set,SIGNAL(sig(GroupAnt*,int)),this,SLOT(setAntAH(GroupAnt*,int)));
    disconnect(add,SIGNAL(sig(TypeOfSector,int)),this,SLOT(addSectAH(TypeOfSector,int)));
    disconnect(addW,SIGNAL(set(GroupAnt*,int)),this,SLOT(setAntW(GroupAnt*,int)));
    delete antHill;
    delete world;
    delete add;
    delete addW;
    delete set;
    clearStore();
    ui->label->setText("Шаг: NaN");
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


void MainWindow::sectorAH(int a){
    if(antHill->getButtons()[a]->onBusy()){
        return;
    }else if(antHill->getMater().second>=5){
        add->add(a);
        add->show();
    }else{
        (new QMessageBox(QMessageBox::Warning,"Нет ресурсов","Не хватает " +
                         QString::number(5-antHill->getMater().second)+
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
    ui->addAnt->setEnabled(true);
}

void MainWindow::disableButtons(){
    //Отключение основных кнопок управния на основной форме
    ui->step->setDisabled(true);
    ui->addAnt->setDisabled(true);
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
