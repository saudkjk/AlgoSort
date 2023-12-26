// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A8
#include "bucketview.h"
#include "level.h"
#include "mainwindow.h"

#include <QPainter>
#include <QPushButton>
#include <QRandomGenerator>
#include <algorithm>
#include <random>
#include <cmath>

#include <cstdlib>
#include <ctime>
#include <iostream>

Level::Level(QWidget *parent)
    : QWidget{parent},
      world(b2Vec2(0.0f, 9.8f))
{
    mainLayout = new QVBoxLayout(this);
    topLayout = new QHBoxLayout();
    bottomLayout = new QHBoxLayout();
    bucketWidget = new QWidget();
    bucketLayout = new QVBoxLayout(bucketWidget);

    messageLayout = new QVBoxLayout();
    messageLabel = new QLabel("");
    QFont messageFont = messageLabel->font();
    messageFont.setPointSize(24);
    messageLabel->setFont(messageFont);
    messageLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    errorLabel = new QLabel("");
    errorLabel->setStyleSheet("color: red;");
    QFont errorFont = errorLabel->font();
    errorFont.setPointSize(18);
    errorLabel->setFont(errorFont);
    errorLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    messageLayout->addWidget(messageLabel);
    messageLayout->addWidget(errorLabel);
    messageLayout->addStretch();

    topLayout->addWidget(bucketWidget);
    topLayout->addStretch();
    topLayout->addLayout(messageLayout);

    mainLayout->addLayout(topLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(bottomLayout);

    bucketWidget->hide();
}

void Level::showEvent(QShowEvent* event) {
    initPhysicsWorld();
    levelSetup();

// setup of items and buckets should be in subclass
// this is just for testing
//    createItems(1, 6);
//    for(Item& item : itemPool) {
//        items.push_back(&item);
//    }
//    Bucket bucket;
//    bucket.title = "Bucket 1";
//    bucket.items.push_back(items[0]);
//    bucket.items.push_back(items[1]);
//    buckets.push_back(bucket);
//    showBuckets();

    connect(&timer, &QTimer::timeout, this, &Level::timerTick);
    // roughly 60 fps
    timer.start(16);
}

void Level::levelSetup() {

}

void Level::timerTick() {
    int velocityIterations = 8;
    int positionIterations = 3;

    qint64 msecsElapsed = highResTimer.elapsed();
    highResTimer.restart();
    world.Step(msecsElapsed / 1000.0, velocityIterations, positionIterations);

    bool allItemsStill = true;
    for(Item* item : items) {
        if(item->body->GetLinearVelocity().Length() > 0.1) {
            allItemsStill = false;
            break;
        }
    }

    // only validate if all items are still and user is not dragging
    if(allItemsStill && draggedItem == nullptr) {
        auto compareItems = [](Item* left, Item* right) {
            return left->body->GetPosition().x < right->body->GetPosition().x;
        };

        std::vector<Item*> sortedItems(items);

        std::sort(sortedItems.begin(), sortedItems.end(), compareItems);

        for(Item* item : sortedItems) {
            item->highlighted = false;
            item->valid = true;
        }

        validate(sortedItems);
    }

    errorCounter++;
    if(errorCounter >= 120) {
        setErrorMessage("");
    }

    update();
    repaint();
}

void Level::paintEvent(QPaintEvent*) {

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(0, 0, this->width(), this->height(), backgroundColor);

    int floorHeight = simYtoViewY(2);
    painter.fillRect(0, this->height() - floorHeight, this->width(), floorHeight, backgroundColor.darker());

    painter.setPen(QPen(Qt::black));
    painter.setBrush(QBrush(Qt::red));
    QFont font = painter.font();
    font.setPointSize(18);
    painter.setFont(font);

    blinkCounter++;
    if(blinkCounter >= 60) {
        blinkCounter = 0;
    }
    for(Item* item : items) {
        int viewX = simXtoViewX(item->body->GetPosition().x);
        int viewY = simYtoViewY(item->body->GetPosition().y);
        if(blinkCounter >= 30 && item->highlighted) {
            painter.setBrush(QBrush(item->color.lighter()));
        }
        else {
            painter.setBrush(QBrush(item->color));
        }

        painter.setPen(Qt::NoPen);
        painter.drawEllipse(QPoint(viewX, viewY), simXtoViewX(item->radius), simYtoViewY(item->radius));
        QString itemValue = QString::number(item->value);
        QRect textRect = painter.fontMetrics().boundingRect(itemValue);
        QPoint textBaseline(viewX - textRect.width() / 2, viewY + textRect.height() / 4);

        // TODO: draw red if invalid
        if(!item->valid) {
            painter.setPen(QPen(Qt::red));
        }
        else {
            painter.setPen(QPen(item->textColor));
        }
        painter.drawText(textBaseline, itemValue);
    }
}

int Level::simXtoViewX(float simX) {
    return (int)(simX * (this->width() / simWidth));
}

float Level::viewXtoSimX(int viewX) {
    return viewX * (simWidth / this->width());
}

int Level::simYtoViewY(float simY) {
    return (int)(simY * (this->height() / simHeight));
}

float Level::viewYtoSimY(int viewY) {
    return viewY * (simHeight / this->height());
}

void Level::initPhysicsWorld() {
    simHeight = 10;
    simWidth = ((float)this->width() / (float)this->height()) * simHeight;

    // setup top wall as a rect (simWidth x 1)
    topWall = createWall(b2Vec2(simWidth / 2, -0.5), simWidth, 1);
    bottomWall = createWall(b2Vec2(simWidth / 2, simHeight - 1.5), simWidth, 1);
    leftWall = createWall(b2Vec2(-0.5, simHeight / 2), 1, simHeight);
    rightWall = createWall(b2Vec2(simWidth + 0.5, simHeight / 2), 1, simHeight);
    dummyWall = createWall(b2Vec2(simWidth / 2, simHeight + 2), 1, 1);

}

b2Body* Level::createWall(b2Vec2 pos, float width, float height) {
    b2BodyDef bodyDef;
    bodyDef.position = pos;

    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape box;
    box.SetAsBox(width / 2, height / 2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.restitution = 0.1;
    fixtureDef.density = 0;
    fixtureDef.friction = 0.5;

    body->CreateFixture(&box, 0);

    return body;
}

void Level::validate(std::vector<Item*> items) {
    if(items.size() <= 1)
        return;

    items[0]->valid = true;
    for(int i = 1; i < items.size(); i++) {
        if(items[i]->value < items[i - 1]->value) {
            items[i]->valid = false;
        }
        else {
            items[i]->valid = true;
        }
    }
}

void Level::showBuckets() {
    QLayoutItem* item;
    while ((item = bucketLayout->takeAt(0)) != nullptr) {
        if(item->widget())
            delete item->widget();
        delete item;
    }
    bucketLayout->addSpacing(30);
    for(auto& pair : buckets) {
        bucketLayout->addWidget(new BucketView(&pair.second));
    }

    bucketLayout->addStretch();

    bucketWidget->show();
}

void Level::randomizeBalls()
{
    for(int i = 0; i < items.size(); i++)
    {
        // random vector with positive y
        float randomX = QRandomGenerator::global()->bounded(2000.0)-1000.0;
        float randomY = QRandomGenerator::global()->bounded(1000.0);

        // normalize vector
        float mag = sqrt(randomX * randomX + randomY * randomY);
        randomX /= mag;
        randomY /= mag;

        items[i]->body->SetLinearVelocity(b2Vec2(randomX*500, randomY*500));
    }

}

void Level::hideBuckets() {
    bucketWidget->hide();
}

void Level::setPromptMessage(QString message) {
    messageLabel->setText(message);
}

void Level::setErrorMessage(QString message) {
    errorCounter = 0;
    errorLabel->setText(message);
}

void Level::gameWon(int level) {
     beaten = true;
}

void Level::createItems(int min, int max, int step, bool shuffled) {
    // note: +1 to make max inclusive
    int numItems = (max + 1 - min) / step;

    std::vector<int> shuffledValues;
    for(int i = 0; i < numItems; i++) {
        int value = min + step * i;
        shuffledValues.push_back(value);
    }
    if(shuffled) {
        std::default_random_engine rng(time(nullptr));
        std::shuffle(shuffledValues.begin(), shuffledValues.end(), rng);
        // make sure the first index isn't the smallest, useful for demonstration
        if(shuffledValues[0] == min) {
            int randomIndex = QRandomGenerator::global()->bounded(1, numItems);
            shuffledValues[0] = shuffledValues[randomIndex];
            shuffledValues[randomIndex] = min;
        }
    }

    for(int i = 0; i < numItems; i++) {
        int value = shuffledValues[i];
        float itemY = simHeight / 2;
        float itemX = (i + 1) * simWidth / (numItems + 1);
        Item item;
        item.value = value;
        item.radius = itemRadius;
        item.valid = true;
        item.highlighted = false;

        // TODO: interpolate between maxColor and minColor
        QColor minHsv = minColor.toHsv();
        QColor maxHsv = maxColor.toHsv();
        float minHue;
        float minSat;
        float minVal;
        minHsv.getHsvF(&minHue, &minSat, &minVal);
        float maxHue;
        float maxSat;
        float maxVal;
        maxHsv.getHsvF(&maxHue, &maxSat, &maxVal);
        float hue = minHue + (maxHue - minHue) * ((float) (value - min) / (max - min));
        float sat = minSat + (maxSat - minSat) * ((float) (value - min) / (max - min));
        float val = minVal + (maxVal - minVal) * ((float) (value - min) / (max - min));
        QColor hsvColor = QColor().toHsv();
        hsvColor.setHsvF(hue, sat, val);
        item.color = hsvColor.toRgb();

        item.bodyDef.type = b2_dynamicBody;
        item.bodyDef.fixedRotation = true;
        item.bodyDef.position.Set(itemX, itemY);

        itemPool.push_back(item);
    }
}

void Level::addToSim(Item* item) {
    item->body = world.CreateBody(&item->bodyDef);

    b2CircleShape circle;
    circle.m_radius = item->radius;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = 1;
    fixtureDef.restitution = 0.4;
    fixtureDef.friction = 0.1;

    item->body->CreateFixture(&fixtureDef);

    items.push_back(item);
}

void Level::removeFromSim(Item* item) {
    if(item == draggedItem) {
        draggedItem = nullptr;
    }

    if(mouseJoint) {
        world.DestroyJoint(mouseJoint);
        mouseJoint = nullptr;
    }

    if(item->body != nullptr) {
        item->bodyDef.position = item->body->GetPosition();
        world.DestroyBody(item->body);
        item->body = nullptr;
    }

    items.erase(std::remove(items.begin(), items.end(), item), items.end());
}

void Level::mousePressEvent(QMouseEvent* event) {
    float clickX = viewXtoSimX(event->position().x());
    float clickY = viewYtoSimY(event->position().y());

    Item* clickedItem = nullptr;
    for(Item* item : items) {
        float dx = item->body->GetPosition().x - clickX;
        float dy = item->body->GetPosition().y - clickY;
        float distance2 = dx * dx + dy * dy;
        float radius2 = item->radius * item->radius;
        if(distance2 < radius2) {
            clickedItem = item;
            break;
        }
    }
    if(clickedItem == nullptr) {
        return;
    }

    draggedItem = clickedItem;

    b2Body* body = clickedItem->body;
    b2MouseJointDef jd;
    jd.bodyA = dummyWall;
    jd.bodyB = body;
    jd.target = b2Vec2(clickX, clickY);
    jd.maxForce = 1000.0f * body->GetMass();

    mouseJoint = (b2MouseJoint*)world.CreateJoint(&jd);
    body->SetAwake(true);

    mouseMoveEvent(event);
}

void Level::mouseReleaseEvent(QMouseEvent* event) {
    if(draggedItem) {
        draggedItem = nullptr;
    }

    if(mouseJoint) {
        world.DestroyJoint(mouseJoint);
        mouseJoint = nullptr;
    }
}

void Level::mouseMoveEvent(QMouseEvent* event) {
    if(mouseJoint) {
        float clickX = viewXtoSimX(event->position().x());
        float clickY = viewYtoSimY(event->position().y());
        mouseJoint->SetTarget(b2Vec2(clickX, clickY));
    }
}
