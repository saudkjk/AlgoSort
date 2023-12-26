// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A8
#include "bogosortlevel.h"

#include <QRandomGenerator>

///
/// \brief Default parent constructor
/// \param parent
///
BogoSortLevel::BogoSortLevel(QWidget* parent) : Level(parent)
{
    backgroundColor = QColor(0x88, 0xA3, 0xB3);
    minColor = QColor(0x00, 0xF3, 0x7E);
    maxColor = QColor(0x00, 0x90, 0x70);
}

///
/// \brief Sets up balls and intro message
///
void BogoSortLevel::levelSetup() {
    createItems(10, 15);
    for(Item& item : itemPool) {
        addToSim(&item);
    }

    setPromptMessage("Tap to randomize the balls");
}

///
/// \brief Validates the state of the items to set relevant prompt messages / state
/// \param items - the items to validate
///
void BogoSortLevel::validate(std::vector<Item*> items) {
    readyForClick = true;

    for(int i = 1; i < items.size(); i++) {
        if(items[i]->value < items[i-1]->value)
           break;

        if(i == items.size() - 1)
        {
             setPromptMessage("Wow! You bogosorted them!");
             gameWon(3);
             return;
        }
    }


   if(timesRandomized == 1)
   {
        setPromptMessage("So close! I'm sure you'll get it soon");
   }
   else if(timesRandomized == 3)
   {
        setPromptMessage("Yep, any time now..");
   }
   else if(timesRandomized == 10)
   {
        setPromptMessage("Are you like, not trying or something?");
   }
   else if(timesRandomized == 15)
   {
        setPromptMessage("C'mon now this is getting ridiculous.");
   }
   else if(timesRandomized == 20)
   {
        setPromptMessage("Alright you're on your own");
   }

}

///
/// \brief Overrides mouse press event for BogoSort to randomize instead of allowing dragging
/// \param event
///
void BogoSortLevel::mousePressEvent(QMouseEvent* event)
{
    if(readyForClick) {
        readyForClick = false;
        timesRandomized++;
        randomizeBalls();
    }
}
