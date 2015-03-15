#ifndef INTERFACE_H
#define INTERFACE_H

#include "levelobject.h"
#include "movablelabel.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QString>

class Interface {
    Interface();
    static Interface instance;
    static Ui::MainWindow* ui;
public:
    //singleton class
    static Interface getInstance();

    //set the ui element for use in manipulating stuff on the screen
    static void setUi(Ui::MainWindow* initUi);

    //draw the object on the screen
    void drawObject(LevelObject* obj);

    //move the object around on the screen
    void moveObject(LevelObject* obj);

    //take the object representing the LevelObject off the screen
    void deleteObject(LevelObject* obj);
};

#endif // INTERFACE_H
