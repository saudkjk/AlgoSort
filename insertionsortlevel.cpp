// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A8
#include "insertionsortlevel.h"
#include <QRandomGenerator>

InsertionSortLevel::InsertionSortLevel(QWidget* parent) : Level(parent)
{
    itemRadius = 0.5;
    backgroundColor = QColor(0x88, 0xEA, 0xFF);
    minColor = QColor(0xC1, 0x8C, 0xFF);
    maxColor = QColor(0xC5, 0x00, 0xFF);
}

/// @brief setting up the insertion sort level by adding items to sort 
void InsertionSortLevel::levelSetup() {
    Level::createItems(1, 12);
    for(Item& item : itemPool) {
        Level::addToSim(&item);
    }
}

/// @brief validate that items are sorted following insertion sort  and print messages to user 
/// @param items items in the simulation
void InsertionSortLevel::validate(std::vector<Item*> items) {
    // find the first index that is not sorted
    int sortIndex = 1;
    for(; sortIndex < 12; sortIndex++) {
        if(items[sortIndex]->value < items[sortIndex - 1]->value)
            break;
    }
    if(sortIndex < lastSortIndex) {
        setErrorMessage("You moved a sorted item!");
    }
    bool progressMade = lastSortIndex < sortIndex && lastSortIndex != -1;
    lastSortIndex = sortIndex;
    if(sortIndex == 12) {
        setPromptMessage("You win!");
        gameWon(0);
        return;
    }

    items[sortIndex]->highlighted = true;

    if(messageIndex == 0) {
        setPromptMessage("Move the current item to the correct spot on the left");
    }
    if(messageIndex == 1) {
        setPromptMessage("Well done!\nNow move the next item to the correct spot");
    }
    if(messageIndex == 2) {
        setPromptMessage("Great!\nNow move the next item to the correct spot");
    }
    if(messageIndex >= 3) {
        setPromptMessage("You got it!\nNow repeat until sorted");
    }
    if(progressMade) {
        messageIndex++;
    }
}
