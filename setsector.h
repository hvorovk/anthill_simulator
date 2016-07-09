#ifndef SETSECTOR_H
#define SETSECTOR_H

#include <QDialog>
#include "world.h"
namespace Ui {
class SetSector;
}

class SetSector : public QDialog
{
    Q_OBJECT
public slots:
    void get(QVector<GroupAnt *> free,int pos,GroupAnt *curr);
    void alpha();
signals:
    set(GroupAnt*,int);
public:
    explicit SetSector(QWidget *parent = 0);
    ~SetSector();
private:
    Ui::SetSector *ui;
    QVector<GroupAnt *> free;
    int pos;

};

#endif // SETSECTOR_H
