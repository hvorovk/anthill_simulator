#ifndef SECTORDIALOG_H
#define SECTORDIALOG_H

#include <QDialog>

namespace Ui {
class SectorDialog;
}

class SectorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SectorDialog(QWidget *parent = 0);
    ~SectorDialog();

private:
    Ui::SectorDialog *ui;
};

#endif // SECTORDIALOG_H
