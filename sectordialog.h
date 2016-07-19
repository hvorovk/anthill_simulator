#ifndef SECTORDIALOG_H
#define SECTORDIALOG_H

#include <QDialog>
#include <anthill.h>

namespace Ui {
class SectorDialog;
}

class SectorDialog : public QDialog
{
    Q_OBJECT
signals:
    sig(TypeOfSector a,int q);
public:
    explicit SectorDialog(QWidget *parent = 0);
    ~SectorDialog();

private:
    int b;
    Ui::SectorDialog *ui;
public slots:
    void sigS();
    void add(int a){
        b = a;
    }
};

#endif // SECTORDIALOG_H
