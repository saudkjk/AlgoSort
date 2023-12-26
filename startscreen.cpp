// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A8
#include "startscreen.h"
#include "ui_startscreen.h"

StartScreen::StartScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartScreen)
{
    ui->setupUi(this);
    setLayout(ui->gridLayout);
}

StartScreen::~StartScreen()
{
    delete ui;
}

///
/// \brief Slot for level select button
///
void StartScreen::on_levelsButton_clicked()
{
    emit startSetScreen(Screen::SCREEN_LEVELS);
}

/// @brief Slot for going to next level
void StartScreen::on_startButton_clicked()
{
     emit startSetScreen(Screen::SCREEN_NEXT_LEVEL);
}

