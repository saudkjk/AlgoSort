// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A8
#ifndef BUCKETVIEW_H
#define BUCKETVIEW_H

#include "level.h"

#include <QWidget>
#include <vector>

class BucketView : public QWidget
{
    Q_OBJECT
public:
    explicit BucketView(Bucket* bucket, QWidget *parent = nullptr);

private:
    std::vector<Item*> items;
    std::vector<QLabel*> labels;
    void paintEvent(QPaintEvent* e);

signals:

};

#endif // BUCKETVIEW_H
