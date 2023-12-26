// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A8
#ifndef MERGESORT_H
#define MERGESORT_H

#include "EnumTypes.h"
#include <QWidget>

namespace Ui {
class MergeSort;
}

class MergeSort : public QWidget
{
    Q_OBJECT

public:
    explicit MergeSort(QWidget *parent = nullptr);
    ~MergeSort();

private:
    Ui::MergeSort *ui;

signals:
    void mergeSwitchScreen(Screen screen);
    void mergeBeatLevel(int level);
private slots:
    void on_menuButton_clicked();
};

#endif // MERGESORT_H
