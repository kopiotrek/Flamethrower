#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QtMath>
#include <QLabel>
#include <QMovie>
#include <QPicture>
#include <QPointF>
#include <QString>
#include "reader.h"


class MyWidget : public QWidget
{
    Q_OBJECT
    Reader r;
public:
    explicit MyWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    double theta = 0;
    int frameNumber = 0;
    bool startup = false;

private:
    void startAnimation();
    void animate();
    void getLean();
};

#endif // MYWIDGET_H
