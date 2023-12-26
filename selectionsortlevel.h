// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A8
#ifndef SELECTIONSORTLEVEL_H
#define SELECTIONSORTLEVEL_H

#include "level.h"
#include "EnumTypes.h"

class SelectionSortLevel : public Level
{
    Q_OBJECT
public:
    SelectionSortLevel(QWidget* parent = nullptr);

private:
    void levelSetup();
    void validate(std::vector<Item*> items);

    int lastSortIndex = 0;
};

#endif // SELECTIONSORTLEVEL_H
