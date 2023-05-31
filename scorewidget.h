#ifndef SCOREWIDGET_H
#define SCOREWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

class scorewidget : public QWidget {
    int score = 0;
public slots:
    void receiveScore(int);
public:
    scorewidget(QWidget *parent = nullptr);
    void displayScore();
};


#endif // SCOREWIDGET_H
