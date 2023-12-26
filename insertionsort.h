// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A8
#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include <QMainWindow>
#include "EnumTypes.h"

namespace Ui {
class InsertionSort;
}

class InsertionSort : public QMainWindow
{
    Q_OBJECT

public:
    explicit InsertionSort(QWidget *parent = nullptr);
    ~InsertionSort();

private:
    Ui::InsertionSort *ui;

signals:
    void insertionSetScreen(Screen screen);
    void insertionBeatLevel(int level);
private slots:
    void on_menuButton_clicked();
};

#endif // INSERTIONSORT_H
