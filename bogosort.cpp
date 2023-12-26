// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A8
#include "bogosort.h"
#include "ui_bogosort.h"

BogoSort::BogoSort(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BogoSort)
{
    ui->setupUi(this);
}

BogoSort::~BogoSort()
{
    delete ui;
}

/// @brief switch to bogo sort level
void BogoSort::on_menuButton_clicked()
{
    emit bogoSetScreen(Screen::SCREEN_LEVELS);
}

