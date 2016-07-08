#ifndef SETSECTOR_H
#define SETSECTOR_H

#include <QDialog>

namespace Ui {
class SetSector;
}

class SetSector : public QDialog
{
    Q_OBJECT

public:
    explicit SetSector(QWidget *parent = 0);
    ~SetSector();

private:
    Ui::SetSector *ui;
};

#endif // SETSECTOR_H
