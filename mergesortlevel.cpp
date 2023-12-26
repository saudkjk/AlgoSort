// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A8
#include "mergesortlevel.h"
#include <QPushButton>

MergeSortLevel::MergeSortLevel(QWidget* parent) : Level(parent),
    left(nullptr),
    right(nullptr),
    mergeIndex(0),
    mergeLength(0),
    leftButton(nullptr),
    rightButton(nullptr)
{
    backgroundColor = QColor(0xEC, 0xC8, 0xAE);
    minColor = QColor(0xB3, 0x67, 0x9B);
    maxColor = QColor(0x6C, 0x4B, 0x5E);
}

/// @brief setting up the merge sort level by adding items to sort, special layout,
///         right and left items for player to click to start sorting.
void MergeSortLevel::levelSetup() {
    leftButton = new QPushButton("left");
    leftButton->setFixedWidth(75);
    leftButton->setFixedHeight(75);
    QFont leftFont = leftButton->font();
    leftFont.setPointSize(18);
    leftButton->setFont(leftFont);
    rightButton = new QPushButton("right");
    rightButton->setFixedWidth(75);
    rightButton->setFixedHeight(75);
    QFont rightFont = rightButton->font();
    rightFont.setPointSize(18);
    rightButton->setFont(rightFont);

    bottomLayout->addStretch();
    bottomLayout->addWidget(leftButton);
    bottomLayout->addWidget(rightButton);
    bottomLayout->addStretch();

    QRegion mask = QRegion(QRect(0, 0, 75, 75), QRegion::Ellipse);
    leftButton->setMask(mask);
    rightButton->setMask(mask);

    connect(leftButton, &QPushButton::clicked, this, &MergeSortLevel::leftClicked);
    connect(rightButton, &QPushButton::clicked, this, &MergeSortLevel::rightClicked);

    itemRadius = 0.5;

    createItems(1, 12, 1, true);
    for(int i = 1; i < itemPool.size(); i += 2) {
        Bucket bucket;
        bucket.title = QString("Bucket ") + QString((char)('A' + i / 2));
        if(itemPool[i].value > itemPool[i - 1].value) {
            bucket.items.push_back(&itemPool[i - 1]);
            bucket.items.push_back(&itemPool[i]);
        }
        else {
            bucket.items.push_back(&itemPool[i]);
            bucket.items.push_back(&itemPool[i - 1]);
        }
        buckets[bucket.title] = bucket;
        bucketsToMerge.push(bucket.title);
    }

    startMerge();

    // add one-time hint to the message

    showBuckets();
}
void MergeSortLevel::validate(std::vector<Item*> items) {

}
void MergeSortLevel::mousePressEvent(QMouseEvent*) {

}

/// @brief Handles mergeing buckets after sorting
void MergeSortLevel::startMerge() {
    if(mergeLength != 0) {
        buckets.erase(right->title);
        if(buckets.size() == 1) {
            setPromptMessage("You win!");
            hideBuckets();
            gameWon(2);
            mergeIndex = 0;
            return;
        }

        std::vector<Item*>& leftItems = buckets[left->title].items;
        leftItems.insert(leftItems.end(), currentMerge.begin(), currentMerge.end());

        for(Item* item : currentMerge) {
            removeFromSim(item);
        }

        bucketsToMerge.push(left->title);
    }

    currentMerge.clear();

    left = &buckets[bucketsToMerge.front()];
    bucketsToMerge.pop();
    right = &buckets[bucketsToMerge.front()];
    bucketsToMerge.pop();
    mergeIndex = 0;
    mergeLength = left->items.size() + right->items.size();

    setPromptMessage(QString("Merging ") + left->title + " and " + right->title + "\n(Select the smaller item)");

    updateButtons();

    leftButton->setDisabled(false);
    rightButton->setDisabled(false);

    showBuckets();
}

/// @brief handles player choice for sorting. Calls startMerge if player choice is correct sends message to player if not. 
/// @param clicked bucket player clicked
/// @param other   the other bucket
void MergeSortLevel::handleClick(Bucket* clicked, Bucket* other) {
    if(clicked->items.size() == 0) {
        setErrorMessage(clicked->title + " is empty!");
        return;
    }

    if(other->items.size() == 0 || clicked->items[0]->value < other->items[0]->value) {
        clicked->items[0]->bodyDef.position.Set((mergeIndex + 1) * (simWidth / (mergeLength + 1)), simHeight / 2);
        addToSim(clicked->items[0]);
        currentMerge.push_back(clicked->items[0]);
        clicked->items.erase(clicked->items.begin());
        showBuckets();
        mergeIndex++;

        updateButtons();

        if(mergeIndex == mergeLength) {
            leftButton->setDisabled(true);
            rightButton->setDisabled(true);
            QTimer::singleShot(2000, std::bind(&MergeSortLevel::startMerge, this));
        }
    }
    else {
        setErrorMessage(other->title + " has a lower value to pick!");
    }
}

void MergeSortLevel::updateButtons() {
    if(left->items.size() == 0) {
        leftButton->setText("");
        leftButton->setDisabled(true);
        leftButton->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    }
    else {
        leftButton->setText(QString::number(left->items[0]->value));
        leftButton->setStyleSheet(QString("border: none; background-color: ") + left->items[0]->color.name());
    }
    if(right->items.size() == 0) {
        rightButton->setText("");
        rightButton->setDisabled(true);
        rightButton->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    }
    else {
        rightButton->setText(QString::number(right->items[0]->value));
        rightButton->setStyleSheet(QString("border: none; background-color: ") + right->items[0]->color.name());
    }
}

/// @brief handle player clicked left item
void MergeSortLevel::leftClicked() {
    handleClick(left, right);
}

/// @brief handle player clicked right item
void MergeSortLevel::rightClicked() {
    handleClick(right, left);
}
