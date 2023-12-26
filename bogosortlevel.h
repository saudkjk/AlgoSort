// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A8
#ifndef BOGOSORTLEVEL_H
#define BOGOSORTLEVEL_H

#include "level.h"


class BogoSortLevel : public Level
{
    Q_OBJECT
public: 
    BogoSortLevel(QWidget* parent = nullptr);

private:
    void levelSetup();
    void validate(std::vector<Item*> items);
    void mousePressEvent(QMouseEvent* event) override;

    int timesRandomized = 0;
    bool readyForClick = true;
};

#endif // BOGOSORTLEVEL_H
