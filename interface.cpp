#include "interface.h"
#include "levelmanager.h"
#include <QString>
#include <QDebug>
#include <QLabel>
#include <QMessageBox>

Interface::Interface() {}

Interface Interface::instance;

Ui::MainWindow* Interface::ui;

Interface Interface::getInstance() {
    return instance;
}

void Interface::setUi(Ui::MainWindow *initUi) {
    ui = initUi;
}

void Interface::drawObject(LevelObject* obj) {
    int id = obj->getId();
    QWidget* area = (ui->gameArea);
    QLabel* lbl = new QLabel(area);
    lbl->setText(QString::number(id));
    lbl->setGeometry(obj->getGeometry());
    lbl->setStyleSheet("QLabel {color:red; background-color: red;}");
    lbl->show();
}

void Interface::moveObject(LevelObject *obj) {
    for(QObject* obj2: ui->gameArea->children()) {
        QLabel* lbl = dynamic_cast<QLabel*>(obj2);
        if (lbl == nullptr) {
            continue;
        }
        if (lbl->text() == QString::number(obj->getId())) {
            //correct label
            //move the label to the new position
            lbl->setGeometry(obj->getGeometry());
        }
    }
}

void Interface::deleteObject(LevelObject *obj) {
    for(QObject* obj2: ui->gameArea->children()) {
        QLabel* lbl = dynamic_cast<QLabel*>(obj2);
        if (lbl == nullptr) {
            continue;
        }
        if (lbl->text() == QString::number(obj->getId())) {
            //correct label
            //hide and then delete the label
            lbl->hide();
            lbl->deleteLater();
        }
    }
}

void Interface::showTime(QString str) {
    ui->timeLeft->setText(str);
}

void Interface::showVictory() {
        QMessageBox *banner = new QMessageBox(ui->gameArea);

        if(LevelManager::getInstance().getLevel() < 9){
            //display the message
            banner->setText("Congratulations. You've completed this mission soldier.\n\n\n  ---New Mission Unlocked---");
            banner->show();

            //increment the lastUnlockedLevel
            LevelManager::getInstance().incrementLastUnlockedLevel();
            updateGUI();
    }
}

void Interface::updateGUI()
{
    //unlock the next button on the GUI
    for (QObject* obj: ui->levels->children())
    {
        QPushButton* button = dynamic_cast<QPushButton*>(obj);
        if (button != nullptr)
        {
            if (button->text().toInt() <= LevelManager::getLastUnlockedLevel())
            {
                button->setEnabled(true);
            }
        }
     }

    //reset variables for next level
    ui->leUserName->setEnabled(true);
    ui->rbEasy->setCheckable(true);
    ui->rbMedium->setCheckable(true);
    ui->rbHard->setCheckable(true);
    ui->btCheat->setEnabled(true);
}

void Interface::howTo(){
    QMessageBox *explain = new QMessageBox(ui->gameArea);
    explain->setText("Before playing, please insert your name in the box above and hit load to begin your campaign.\nThis is a simple overview of the game's controls.\nControls:\n\n -Right arrow moves the tank right.\n -Down arrow moves the tank down.\n -Left arrow moves the tank left.\n -Up arrow moves the tank up.\n -Click the mouse on the playing field to shoot.\nNOTE: Your bullets will follow the mouse's current position.\n\nTo beat the game, simply be the last tank standing. Good luck.");
    explain->show();
}

void Interface::showDefeat(QString msg){
    QMessageBox *banner = new QMessageBox(ui->gameArea);
    banner->setText(msg);
    banner->show();

    updateGUI();

}
