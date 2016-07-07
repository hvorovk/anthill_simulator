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
    antHill = new AntHill("anthill");
    world = new World();
    add = new SectorDialog();
    //Установка связей
    connect(alpha,SIGNAL(loadSig()),this,SLOT(loadS()));
    connect(alpha,SIGNAL(saveSig()),this,SLOT(saveS()));
    connect(alpha,SIGNAL(newSig()),this,SLOT(newS()));
    connect(alpha,SIGNAL(loadSig()),this,SLOT(loadS()));
    connect(alpha,SIGNAL(overSig()),this,SLOT(overS()));
    connect(alpha,SIGNAL(closed()),this,SLOT(closeMenu()));
    foreach (auto a, antHill->getButtons()) {
        connect(a,SIGNAL(clicked(int)),this,SLOT(sectorAntHill(int)));
    }
    connect(add,SIGNAL(sig(int,int)),this,SLOT(addSectAH(int,int)));
    connect(ui->menu,SIGNAL(clicked()),this,SLOT(openMenu()));
    connect(ui->step,SIGNAL(clicked()),this,SLOT(nextStep()));
    connect(ui->viewMode,SIGNAL(clicked()),this,SLOT(changeViewMode()));

    ui->generalScene->setScene(antHill->getScene());
    disableButtons();
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
}

void MainWindow::nextStep(){
    //Новый шаг симуляции
    antHill->nextStep();
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

void MainWindow::loadS(){
    //Загрузка сессии
    enableButtons();
}

void MainWindow::saveS(){
    //Сохранение сессии

}

void MainWindow::newS(){
    //Новая сессия
    enableButtons();
}

void MainWindow::overS(){
    //Завершение всей программы
    exit(0);
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

MainWindow::~MainWindow()
{
    delete ui;
}
