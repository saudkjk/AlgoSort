// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A8
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "EnumTypes.h"
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int currentLevel = 0;

private:
    Ui::MainWindow *ui;
    QStackedWidget* stackedWidget;



public slots:
     void switchScreen(Screen screen);
     void beatLevel(int level);

};
#endif // MAINWINDOW_H
