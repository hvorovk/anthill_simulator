/*
 * Основная форма
 * Управление игровым процессом.
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "world.h"
#include "menu.h"
#include "sectordialog.h"
#include "setsector.h"
#include "setant.h"
#include "makeant.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void loadS();
    void saveS();
    void newS();
    void overS();
    void exitS();
    void openMenu();
    void closeMenu();
    void nextStep();
    void changeViewMode();
    void sectorAH(int a);
    void sectorW(int a);
    void addSectAH(TypeOfSector, int );
    void enterAH(int);
    void leaveAH();
    void leaveW();
    void setAntW(GroupAnt*,int);
    void enterW(int);
    void remove(int);
    void callToChange(int);
    void setAntAH(GroupAnt*,int);
    void AntMake(Type a);
signals:

public:
    void disableButtons();
    void enableButtons();
    void refreshStore();
    void refreshRepr();
    void clearStore();
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    MakeAnt* make;
    setAnt *set;
    int step;
    SectorDialog *add;
    SetSector *addW;
    AntHill *antHill;
    World *world;
    menu *alpha;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
