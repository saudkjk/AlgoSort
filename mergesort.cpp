// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A8
#include "mergesort.h"
#include "ui_mergesort.h"

MergeSort::MergeSort(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MergeSort)
{
    ui->setupUi(this);
}

MergeSort::~MergeSort()
{
    delete ui;
}

/// @brief switch to mergesort level
void MergeSort::on_menuButton_clicked()
{
   if(ui->level->beaten)
            emit mergeBeatLevel(2);

    emit mergeSwitchScreen(Screen::SCREEN_LEVELS);
}

