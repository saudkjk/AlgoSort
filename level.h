// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A8
#ifndef LEVEL_H
#define LEVEL_H

#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>
#include <QMouseEvent>
#include "Box2D/Box2D.h"

#include <vector>
#include <map>
#include <string>
#include <QGridLayout>
#include <QLabel>

struct Item {
    int value = 0;

    /**
     * @brief indicates that the circle is in the correct sorted location
     */
    bool valid = true;

    /**
     * @brief if true, the item will blink at 2hz
     */
    bool highlighted = false;

    QColor color = Qt::white;
    QColor textColor = Qt::black;

    b2BodyDef bodyDef;
    b2Body* body = nullptr;

    float radius = 0;
};

/**
 * @brief Represents a temporary storage "bucket" used in some algorithms.
 *        The contents of the buckets will be displayed on the left of the screen.
 */
struct Bucket {
    QString title;
    std::vector<Item*> items;
};

class Level : public QWidget
{
    Q_OBJECT
public:
    explicit Level(QWidget *parent = nullptr);
    QVBoxLayout* mainLayout;
    // buttons the user clicks to control the level should go here
    QHBoxLayout* bottomLayout;
    // help and error messages go here
    QHBoxLayout* topLayout;
    QWidget* bucketWidget;
    QVBoxLayout* bucketLayout;
    QVBoxLayout* messageLayout;

    bool beaten = false;

protected:
    QColor backgroundColor = QColor(255, 186, 107);
    QColor minColor = QColor(58, 242, 95);
    QColor maxColor = QColor(58, 95, 242);
    float itemRadius = 1;

    float simWidth = 10;
    float simHeight = 10;

    b2World world;
    b2Body* bottomWall;
    b2Body* leftWall;
    b2Body* rightWall;
    b2Body* topWall;
    // for some reason, the mouse joint needs a wall to connect to, but the
    // object being dragged won't collide with the connected wall, so this
    // is an extra wall outside the game area
    b2Body* dummyWall;

    // responsible for the storage of all items
    std::vector<Item> itemPool;

    // items stashed in buckets
    std::map<QString, Bucket> buckets;

    virtual void levelSetup();

    /**
     * @brief Should be reimplemented by the level
     *        Provides pointers to all items on the board,
     *        sorted by position on the board left-to-right.
     *        Level implementation should mark each item
     *        valid that is in the correct place
     *
     * @param items pointers to items sorted by board position
     */
    virtual void validate(std::vector<Item*> items);

    void showBuckets();
    void hideBuckets();

    /**
     * @brief createItems Creates items and adds them to the pool
     *                    (does not add them to the board yet)
     * @param min minimum value of items
     * @param max maximum value of items
     * @param step step size between each (default 1)
     */
    void createItems(int min, int max, int step = 1, bool shuffled = true);

    /**
     * @brief remove item ffrom world
     * 
     * @param item iterm to add
     */
    void addToSim(Item* item);
    /**
     * @brief remove item ffrom world
     * 
     * @param item item iterm to remove
     */
    void removeFromSim(Item* item);

    /**
     * @brief Sets a message prompting the user what to do next
     */
    void setPromptMessage(QString message);

    /**
     * @brief Sets an error message. This can be used to explain
     *        what a user is doing wrong.
     */
    void setErrorMessage(QString message);

    /**
     * @brief Implementations should call this when the game has
     *        been won, i.e. all items have been sorted
     */
    void gameWon(int level);

    /**
     * @brief Apply random force to all balls on the screen
     */
    void randomizeBalls();

    // conversion methods
    // note: view x is always positive, 0 is left
    //       sim x is -(width / 2) to (width / 2)
    //       positive view y goes down from the top
    //       positive sim y goes up from the bottom
    int simXtoViewX(float simX);
    float viewXtoSimX(int viewX);
    int simYtoViewY(float simY);
    float viewYtoSimY(int viewY);


private:
    QLabel* messageLabel;
    QLabel* errorLabel;

    QTimer timer;
    int blinkCounter = 0;
    int errorCounter = 0;

    // used for time deltas for the physics simulation
    QElapsedTimer highResTimer;

    b2MouseJoint* mouseJoint = nullptr;

    // all items currently on the board
    std::vector<Item*> items;

    Item* draggedItem = nullptr;

    void paintEvent(QPaintEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void showEvent(QShowEvent* event);

    void initPhysicsWorld();
    b2Body* createWall(b2Vec2 pos, float width, float height);

public slots:
    void timerTick();

};

#endif // LEVEL_H
