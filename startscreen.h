// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A8
#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QWidget>
#include "EnumTypes.h"

namespace Ui {
class StartScreen;
}

class StartScreen : public QWidget
{
    Q_OBJECT

public:
    explicit StartScreen(QWidget *parent = nullptr);
    ~StartScreen();

private:
    Ui::StartScreen *ui;

signals:
     void startSetScreen(Screen screen);

private slots:
     void on_levelsButton_clicked();
     void on_startButton_clicked();
};

#endif // STARTSCREEN_H
