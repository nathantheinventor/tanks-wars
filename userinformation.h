//--------------------------------------------------------------
// File:   userinformation.h
// Author: Jordan Fleck  Team: Barnabas  Class: CpS 111
// Desc: This file contains all the information needed to store
//      user save information, as well as highscore, highest
//      level reached, and what level the user is currently on.
//--------------------------------------------------------------

#ifndef USERINFORMATION_H
#define USERINFORMATION_H

#include <QObject>

#include <fstream>
#include <sstream>
using namespace std;

class UserInformation : public QObject {
    Q_OBJECT
    UserInformation(QObject *parent = 0);
    static UserInformation instance;

    //counter to record which level is available
    static int lastUnlockedLevel;

    //The name of the user
    QString userName;

    //current high score of the user
    int userHighScore;

    //used to find the correct level file to save the highScores to
    int currentLevelNumber;

    //the time selected by the user
    QString userTime;

public:
    static UserInformation& getInstance();

    //getter and setter for the time selected by the user
    QString getUserTime();
    void selectTime(QString s);

    void setLevelNumber(int levelNum);

    //returns which level the user was playing
    int getLevel();

    //set userHighScore
    void setHighScore();

    //returns userHighScore
    int getUserHighScore();

    //get the username
    QString getUserName();

    //set the username
    void setUserName(QString name);

    //increment levelUnlockedLevel
    static void incrementLastUnlockedLevel();

    //code used by the load method to set the variable.
    static void setLastUnlockedLevel(int i);

    static int getLastUnlockedLevel();
};

#endif // USERINFORMATION
