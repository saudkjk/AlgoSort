// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A8
#include "selectionsortlevel.h"
#include <QRandomGenerator>

SelectionSortLevel::SelectionSortLevel(QWidget* parent) : Level(parent)
{
    itemRadius = 0.5;
    backgroundColor = QColor(0xCF, 0xBC, 0xE1);
    minColor = QColor(0x00, 0xFF, 0xFF);
    maxColor = QColor(0x00, 0x00, 0xFF);
}
/// @brief setting up the selection sort level by adding items to sort 
void SelectionSortLevel::levelSetup() {
    createItems(1, 12);
    for(Item& item : itemPool) {
        addToSim(&item);
    }

    setPromptMessage("Move the smallest item to the leftmost spot");
}
/// @brief validate that items are sorted following selection sort and print messages to user
/// @param items items in simulation
void SelectionSortLevel::validate(std::vector<Item*> items) {
    // find the first index that is not sorted
    int sortIndex = 0;
    for(; sortIndex < 12; sortIndex++) {
        if(items[sortIndex]->value != sortIndex + 1)
            break;
    }
    if(sortIndex < lastSortIndex) {
        setErrorMessage("You moved a sorted item!\nMove it back!");
    }
    lastSortIndex = sortIndex;
    if(sortIndex == 12) {
        setPromptMessage("You win!");
        gameWon(0);
        return;
    }

    int minimumValue = items[sortIndex]->value;
    int minimumIndex = sortIndex;
    for(int i = sortIndex; i < 12; i++) {
        if(items[i]->value < minimumValue) {
            minimumValue = items[i]->value;
            minimumIndex = i;
        }
    }

    items[minimumIndex]->highlighted = true;

    if(sortIndex == 1) {
        setPromptMessage("Well done!\nNow move the next smallest to the second spot");
    }
    if(sortIndex == 2) {
        setPromptMessage("Great!\nNow move the next smallest to the third spot");
    }
    if(sortIndex >= 3) {
        setPromptMessage("You got it!\nNow repeat until sorted");
    }
}
