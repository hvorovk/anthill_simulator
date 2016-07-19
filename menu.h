/*
 * Меню
 * Основные элементы управления программой.
*/
#ifndef MENU_H
#define MENU_H

#include <QDialog>

namespace Ui {
class menu;
}

class menu : public QDialog
{
    Q_OBJECT
public slots:
    void loadS();
    void saveS();
    void newS();
    void overS();
    void exitS();
    void help();
signals:
    void loadSig();
    void saveSig();
    void newSig();
    void overSig();
    void closed();
    void exitSig();
public:
    explicit menu(QWidget *parent = 0);
    ~menu();

private:
    void closeEvent(QCloseEvent *);
    Ui::menu *ui;
};

#endif // MENU_H
