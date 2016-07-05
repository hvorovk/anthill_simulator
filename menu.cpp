#include "menu.h"
#include "ui_menu.h"
#include <QCloseEvent>

menu::menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
    //Установка связей
    connect(ui->newSim,SIGNAL(clicked()),this,SLOT(newS()));
    connect(ui->loadSim,SIGNAL(clicked()),this,SLOT(loadS()));
    connect(ui->saveSim,SIGNAL(clicked()),this,SLOT(saveS()));
    connect(ui->overSim,SIGNAL(clicked()),this,SLOT(overS()));
    connect(ui->exit,SIGNAL(clicked()),this,SLOT(close()));
}

void menu::loadS(){
    //Загрузка сессии
    emit loadSig();
    close();
}

void menu::saveS(){
    //Сохранение сессии
    emit saveSig();
    close();
}

void menu::newS(){
    //Новая сессия
    emit newSig();
    close();
}

void menu::overS(){
    //Конец работы всей програмы
    emit overSig();
    close();
}

void menu::closeEvent(QCloseEvent *event){
    //Вызов сигнала при выхода из формы
    emit closed();
    event->accept();
}

menu::~menu()
{
    delete ui;
}
