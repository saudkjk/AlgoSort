// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A8
#include "bucketview.h"
#include <QPainter>

BucketView::BucketView(Bucket* bucket, QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* titleLabel = new QLabel(bucket->title);
    QFont font = titleLabel->font();
    font.setBold(true);
    font.setPointSize(12);
    titleLabel->setFont(font);
    layout->addWidget(titleLabel);

    QHBoxLayout* itemsLayout = new QHBoxLayout();
    itemsLayout->addWidget(new QLabel());
    for(Item* item : bucket->items) {
        QLabel* label = new QLabel(QString::number(item->value));
        labels.push_back(label);
        items.push_back(item);
        itemsLayout->addWidget(label);
        itemsLayout->addSpacing(20);
    }
    itemsLayout->addStretch();
    layout->addLayout(itemsLayout);

    repaint();
}
/// @brief the paint event for the mergesort
/// @param  QPaintEvent
void BucketView::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    for(int i = 0; i < (int)items.size(); i++) {
        int x = labels[i]->x() + labels[i]->fontMetrics().horizontalAdvance(QString::number(items[i]->value)) / 2;
        int y = labels[i]->y() + labels[i]->height() / 2;

        painter.setBrush(QBrush(items[i]->color));
        painter.drawEllipse(QPoint(x, y), 12, 12);
    }
}
