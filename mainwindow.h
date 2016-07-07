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
#include "info.h"

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
    void openMenu();
    void closeMenu();
    void nextStep();
    void changeViewMode();
    void sectorAntHill(int a);
    void addSectAH(int, int );
signals:

public:
    void disableButtons();
    void enableButtons();
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    SectorDialog *add;
    AntHill *antHill;
    World *world;
    menu *alpha;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
