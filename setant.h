#ifndef SETANT_H
#define SETANT_H

#include <QDialog>
#include "world.h"

namespace Ui {
class setAnt;
}

class setAnt : public QDialog
{
    Q_OBJECT
public slots:
    void alpha();
    void get(QVector<GroupAnt*> all, int pos, GroupAnt* cur, TypeOfSector type);
signals:
    sig(GroupAnt*,int);
public:

    explicit setAnt(QWidget *parent = 0);
    ~setAnt();
    void clear();

private:
    QVector<GroupAnt*> ant;
    int pos;
    GroupAnt* c;
    Ui::setAnt *ui;
};

#endif // SETANT_H
