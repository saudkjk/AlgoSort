// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A8
#ifndef BOGOSORT_H
#define BOGOSORT_H

#include <QMainWindow>
#include "EnumTypes.h"

namespace Ui {
class BogoSort;
}

class BogoSort : public QMainWindow
{
    Q_OBJECT

public:
    explicit BogoSort(QWidget *parent = nullptr);
    ~BogoSort();

private:
    Ui::BogoSort *ui;

signals:
     void bogoSetScreen(Screen screen);
private slots:
     void on_menuButton_clicked();
};

#endif // BOGOSORT_H
