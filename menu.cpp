#include "menu.h"
#include "ui_menu.h"
#include <QCloseEvent>
#include "help.h"

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
    connect(ui->exit_2,SIGNAL(clicked()),this,SLOT(exitS()));
    connect(ui->help,SIGNAL(clicked()),this,SLOT(help()));
    ui->loadSim->hide();
    ui->saveSim->hide();
}

void menu::help(){
    (new Help())->show();
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

void menu::exitS(){
    emit exitSig();
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
