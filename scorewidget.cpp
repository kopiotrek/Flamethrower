#include "scorewidget.h"

scorewidget::scorewidget(QWidget *parent) : QWidget(parent)
{
    displayScore();
}

void scorewidget::receiveScore(int new_score){
    score=new_score;
}


void scorewidget::displayScore(){
    auto label = new QLabel(QString::number(score), this);
    auto layout = new QHBoxLayout(this);
    layout->addWidget(label);
    setLayout(layout);
}
