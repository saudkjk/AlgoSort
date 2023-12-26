// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A8
#ifndef INSERTIONSORTLEVEL_H
#define INSERTIONSORTLEVEL_H

#include "level.h"

class InsertionSortLevel : public Level
{
    Q_OBJECT
public:
    InsertionSortLevel(QWidget* parent = nullptr);

private:
    void levelSetup();
    void validate(std::vector<Item*> items);

    int lastSortIndex = -1;
    int messageIndex = 0;

};

#endif // INSERTIONSORTLEVEL_H
