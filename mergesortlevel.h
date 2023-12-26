// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A8
#ifndef MERGESORTLEVEL_H
#define MERGESORTLEVEL_H

#include "level.h"

#include <QPushButton>
#include <queue>

class MergeSortLevel : public Level
{
    Q_OBJECT
public:
    MergeSortLevel(QWidget* parent = nullptr);

public slots:
    void leftClicked();
    void rightClicked();

    void startMerge();

private:
    std::queue<QString> bucketsToMerge;
    std::vector<Item*> currentMerge;
    Bucket* left;
    Bucket* right;
    int mergeIndex;
    int mergeLength;
    QPushButton* leftButton;
    QPushButton* rightButton;

    void updateButtons();

    void levelSetup();
    void validate(std::vector<Item*> items);

    void handleClick(Bucket* clicked, Bucket* other);

    // override parent press event to prevent dragging
    void mousePressEvent(QMouseEvent*);
};

#endif // MERGESORTLEVEL_H
