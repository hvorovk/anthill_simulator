#ifndef MAKEANT_H
#define MAKEANT_H

#include <QDialog>
#include "groupant.h"

namespace Ui {
class MakeAnt;
}

class MakeAnt : public QDialog
{
    Q_OBJECT
public slots:
    void alpha();
signals:
    sig(Type a);
public:
    explicit MakeAnt(QWidget *parent = 0);
    ~MakeAnt();

private:
    Ui::MakeAnt *ui;
};

#endif // MAKEANT_H
