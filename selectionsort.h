// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A8
#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H

#include <QMainWindow>
#include "EnumTypes.h"

namespace Ui {
class SelectionSort;
}

class SelectionSort : public QMainWindow
{
    Q_OBJECT

public:
    explicit SelectionSort(QWidget *parent = nullptr);
    ~SelectionSort();

private:
    Ui::SelectionSort *ui;

signals:
     void selectionSetScreen(Screen screen);
     void selectionBeatLevel(int level);
private slots:
     void on_menuButton_clicked();
};

#endif // SELECTIONSORT_H
