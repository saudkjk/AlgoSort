// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A8
#include "insertionsort.h"
#include "ui_insertionsort.h"

InsertionSort::InsertionSort(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InsertionSort)
{
    ui->setupUi(this);
}

InsertionSort::~InsertionSort()
{
    delete ui;
}

/// @brief switch to insertion sort level
void InsertionSort::on_menuButton_clicked()
{
    if(ui->widget->beaten)
             emit insertionBeatLevel(1);

    emit insertionSetScreen(Screen::SCREEN_LEVELS);
}

