#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    connect(alpha,SIGNAL(closed()),this,SLOT(closeMenu()));

    connect(ui->menu,SIGNAL(clicked()),this,SLOT(openMenu()));
    connect(ui->step,SIGNAL(clicked()),this,SLOT(nextStep()));
    connect(ui->viewMode,SIGNAL(clicked()),this,SLOT(changeViewMode()));

    world = new AntHill("suka");
    ui->generalScene->setScene(world->getScene());
    disableButtons();
}

void MainWindow::changeViewMode(){
    //Изменение отображения graphicsview
    //Режим просмотра муравейника или мира.
}

void MainWindow::nextStep(){
    //Новый шаг симуляции
    world->nextStep();
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
    alpha->close();
    this->close();
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
