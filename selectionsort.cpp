// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A8
#include "selectionsort.h"
#include "ui_selectionsort.h"

SelectionSort::SelectionSort(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SelectionSort)
{
    ui->setupUi(this);
}

SelectionSort::~SelectionSort()
{
    delete ui;
}

/// @brief switch to selection sort level
void SelectionSort::on_menuButton_clicked()
{
    if(ui->widget->beaten)
        emit selectionBeatLevel(0);

    emit selectionSetScreen(Screen::SCREEN_LEVELS);
}

SelectionSortLevel getLevel()
{
}
