//--------------------------------------------------------------
// File:   movablelabel.cpp
// Author: Nathan Collins  Login: ncoll943  Class: CpS 111
// Desc: This defines an extension of the QLable that the user can drag around
//--------------------------------------------------------------
#include "world.h"
#include "movablelabel.h"
#include "interface.h"
#include "worldcommand.h"

MovableLabel::MovableLabel(QWidget *parent): QLabel(parent), win(parent) {
    setMouseTracking(true); // enable mouse move events
    mouseDragging = false;
}
void MovableLabel::mouseMoveEvent(QMouseEvent *ev) {
    if (mouseDragging)
        this->move(mapToParent(ev->pos() - this->offset));
}

void MovableLabel::mousePressEvent(QMouseEvent *ev) {
    mouseDragging = true;
    offset = ev->pos(); // location where mouse was clicked within the label
}

//TODO: refine this class for this game
void MovableLabel::mouseReleaseEvent(QMouseEvent *ev) {
    if (Interface::getInstance().getMode() == Selecting) {
        WorldCommand* cmd = new MoveCommand(this->minimumWidth(), this->x(), this->y());
        UndoManager::getInstance().doCommand(cmd);
    } else {
        WorldCommand* cmd = new DestroyCommand(this->minimumWidth());
        UndoManager::getInstance().doCommand(cmd);
    }
    World::getInstance().printWorld();
    mouseDragging = false;
}
