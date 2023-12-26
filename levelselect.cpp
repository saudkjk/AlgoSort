// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A8
#include "levelselect.h"
#include "ui_levelselect.h"
#include "mainwindow.h"

LevelSelect::LevelSelect(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LevelSelect)
{
    ui->setupUi(this);
}

void LevelSelect::setCurrentLevel(int currentLevel)
{
    if(currentLevel < 1) ui->insertionSort->setEnabled(false);
    else ui->insertionSort->setIconSize(QSize(0,0));
    if(currentLevel < 2) ui->mergeSort->setEnabled(false);
    else ui->mergeSort->setIconSize(QSize(0,0));
     if(currentLevel < 3) ui->bogoSort->setEnabled(false);
     else ui->bogoSort->setIconSize(QSize(0,0));
     ui->heapSort->setEnabled(false);
}

LevelSelect::~LevelSelect()
{
    delete ui;
}

///
/// \brief Menu button slot
///
void LevelSelect::on_menuButton_clicked()
{
    emit levelSetScreen(Screen::SCREEN_MENU);
}

///
/// \brief Clicked selection sort
///
void LevelSelect::on_selectionSort_clicked()
{
    emit levelSetScreen(Screen::SCREEN_SELECTIONSORT);
}

///
/// \brief Clicked merge sort
///
void LevelSelect::on_mergeSort_clicked()
{
    emit levelSetScreen(Screen::SCREEN_MERGESORT);
}

///
/// \brief Clicked bogo sort
///
void LevelSelect::on_bogoSort_clicked()
{
    emit levelSetScreen(Screen::SCREEN_BOGOSORT);
}

///
/// \brief Clicked insertion sort
///
void LevelSelect::on_insertionSort_clicked()
{
    emit levelSetScreen(Screen::SCREEN_INSERTIONSORT);
}
