//--------------------------------------------------------------
// File:   levelobject.h
// Author: Nathan Collins  Team: Barnabas  Class: CpS 111
// Desc: This file creates the objects in the world and adds it
//      to the levelmanager.
//--------------------------------------------------------------

#ifndef LEVELOBJECT_H
#define LEVELOBJECT_H

#include <QObject>
#include <QTimer>
#include <QRect>
//#include <QString>

class LevelObject : public QObject {
    Q_OBJECT

protected:
    int id;
    QString imagePath;
    double x, y, width, height;
    bool isMovable;
    bool isDestroyable;
    static int nextId;
    //timer to be used to animate movableObjects
    QTimer* timer;
public:
    explicit LevelObject(int initX, int initY, int initWidth, int initHeight, QObject *parent = 0);

    //getters and setters
    int getId();
    void setId(int x){id = x;}
    bool getIsMovable() {return isMovable;}
    int getX() {return x;}
    int getY() {return y;}

    QString getImagePath();

    //get a rectangle representing the object for calculations especially involving overlapping of objects
    QRect virtual getGeometry();//overriden by bullet and tank so the label size may be changed

    //for objects that are destroyable, blow them up
    virtual void destroy();

    //pause the timer to stop animation
    void pause();

    //resume the timer to restart animation
    void resume();

    ~LevelObject();

    //this 'flag' is a bool that determines if the object is the key to win the game
    virtual bool hasFlag() {return false;}
protected slots:
    //called when the timer goes off
    virtual void onTimeOut();
};

enum Direction {North, South, East, West, nullDirection};

//an object that can move around on the screen, such as a tank or bullet
class MovableObject: public LevelObject {
    Q_OBJECT 

protected:
    //what direction to move
    Direction d;

    //what direction the image is facing
    Direction directionFaced;

public:
    //getters and setters for d and directionFaced
    void setDirectionFaced(Direction direction);
    void setD(Direction direction);
    Direction getD();
    Direction getDirectionFaced();

    //get a rectangle representing the object for calculations especially involving overlapping of objects
    QRect getGeometry(); //overriden for bullet and tank so the label size may be changed

    MovableObject(int initX, int initY, int initWidth, int initHeight, QObject *parent);

    //moves the object to the new location
    virtual void move(int newX, int newY);

    //if the object overlaps with another object, get the object it is in contact with, otherwise return nullptr
    LevelObject * getContactedObject();


};

class TankObject: public MovableObject {
    Q_OBJECT

    //the angle, in degrees, that the turret is facing
    int turretAngle;

public:
    TankObject(int x, int y, QObject* parent = 0);

    //move the tank to the new location
    void move(int newX, int newY);

    //when the user holds down a particular arrow key, start the tank moving
    void startMotion(Direction d);

    //stop the tank from moving
    void stopMotion();

    //aim the turret in that direction
    void setTurret(int angle);

    //blow up the tank
    void destroy();
public slots:
    //move 5px in the direction specified
    void onTimeOut();
};

class BulletObject: public MovableObject  {
    Q_OBJECT

    //the angle, in degrees, that the bullet is moving
    double heading;
    TankObject* tank;
public:
    BulletObject(int initX, int initY, double initHeading, TankObject* initTank, QObject* parent = 0);

    //move the bullet
    void move(int newX, int newY);

    //set the timer to start the bullet moving
    void startMotion();

public slots:
    //move the bullet 5px in the direction specified by <heading>
    void onTimeOut();
};

class WallObject: public LevelObject {
    Q_OBJECT

public:
    WallObject(int x, int y, int width, int height, QObject* parent = 0);
};

class Barricade: public LevelObject {
    Q_OBJECT

public:
    Barricade(int x, int y, QObject* parent = 0);
};

class Target: public TankObject {
    Q_OBJECT

public:
    Target(int x, int y, QObject* parent = 0);
    bool hasFlag() {return true;}

    //when the enemy tank gets hit, destroy it and win the game
    void destroy();
};

#endif // LEVELOBJECT_H
