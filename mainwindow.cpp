// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A8
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "startscreen.h"
#include "levelselect.h"
#include "selectionsort.h"
#include "mergesort.h"
#include "bogosort.h"
#include "insertionsort.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(new StartScreen(this));

    setCentralWidget(stackedWidget);

    switchScreen(Screen::SCREEN_MENU);

}
/// @brief counter too keep track of user progress
/// @param level 
void MainWindow::beatLevel(int level)
{
    currentLevel = level+1;
}

/// @brief switching between different levels
/// @param screen 
void MainWindow::switchScreen(Screen screen)
{
    // remove the current screen, if it exists
    if(stackedWidget->count() > 0)
    {
        QWidget* widget = stackedWidget->widget(0);
        stackedWidget->removeWidget(widget);
        widget->deleteLater();
    }

    // add the new selected screen
    if(screen == Screen::SCREEN_MENU)
    {
        StartScreen* startScreen = new StartScreen(this);
        stackedWidget->addWidget(startScreen);
        connect(startScreen, &StartScreen::startSetScreen, this, &MainWindow::switchScreen);
    }
    else if(screen == Screen::SCREEN_LEVELS)
    {
        LevelSelect* levelSelect = new LevelSelect(this);
        levelSelect->setCurrentLevel(currentLevel);
        stackedWidget->addWidget(levelSelect);
        connect(levelSelect, &LevelSelect::levelSetScreen, this, &MainWindow::switchScreen);
    }
    else if(screen == Screen::SCREEN_SELECTIONSORT || (screen == Screen::SCREEN_NEXT_LEVEL && currentLevel == 0))
    {
        SelectionSort* selectionSort = new SelectionSort(this);
        stackedWidget->addWidget(selectionSort);
        connect(selectionSort, &SelectionSort::selectionSetScreen, this, &MainWindow::switchScreen);
        connect(selectionSort, &SelectionSort::selectionBeatLevel, this, &MainWindow::beatLevel);
    }
    else if(screen == Screen::SCREEN_MERGESORT || (screen == Screen::SCREEN_NEXT_LEVEL && currentLevel == 2))
    {
        MergeSort* mergeSort = new MergeSort(this);
        stackedWidget->addWidget(mergeSort);
        connect(mergeSort, &MergeSort::mergeSwitchScreen, this, &MainWindow::switchScreen);
        connect(mergeSort, &MergeSort::mergeBeatLevel, this, &MainWindow::beatLevel);
    }
    else if(screen == Screen::SCREEN_BOGOSORT || (screen == Screen::SCREEN_NEXT_LEVEL && currentLevel == 3))
    {
        BogoSort* bogoSort = new BogoSort(this);
        stackedWidget->addWidget(bogoSort);
        connect(bogoSort, &BogoSort::bogoSetScreen, this, &MainWindow::switchScreen);
    }
    else if(screen == Screen::SCREEN_INSERTIONSORT || (screen == Screen::SCREEN_NEXT_LEVEL && currentLevel == 1))
    {
        InsertionSort* insertionSort = new InsertionSort(this);
        stackedWidget->addWidget(insertionSort);
        connect(insertionSort, &InsertionSort::insertionSetScreen, this, &MainWindow::switchScreen);
        connect(insertionSort, &InsertionSort::insertionBeatLevel, this, &MainWindow::beatLevel);
    }
}

MainWindow::~MainWindow()
{
    delete stackedWidget;
    delete ui;
}

