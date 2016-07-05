/*
 * Основная форма
 * Управление игровым процессом.
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "world.h"
#include "menu.h"

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
signals:

public:
    void disableButtons();
    void enableButtons();
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    menu *alpha;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
