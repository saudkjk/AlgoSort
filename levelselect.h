// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A8
#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include <QMainWindow>
#include "EnumTypes.h"

namespace Ui {
class LevelSelect;
}

class LevelSelect : public QMainWindow
{
    Q_OBJECT

public:
    explicit LevelSelect(QWidget *parent = nullptr);
    ~LevelSelect();
    void setCurrentLevel(int currentLevel);

private:
    Ui::LevelSelect *ui;

signals:
     void levelSetScreen(Screen screen);

private slots:
     void on_selectionSort_clicked();
     void on_menuButton_clicked();
     void on_mergeSort_clicked();
     void on_bogoSort_clicked();
     void on_insertionSort_clicked();
};

#endif // LEVELSELECT_H
