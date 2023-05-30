#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    startAnimation();
}

void MyWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillRect(rect(), Qt::black); // Fill the background with black color

    QRectF target(width() * 0.33 , 0.0, height() / 2, width() / 2);    // 576x720
    QRectF source(0.0, 0.0, 576.0, 720.0);
    QString filename = QString("/home/pk/Wizualizacja_danych/assets/side_frames/frame_%1.png")
            .arg(QString::number(frameNumber).rightJustified(3, '0')); // format frame number with leading zeros
    if (frameNumber > 100)
        startup = true;
    if (startup && frameNumber == 130)
        frameNumber = 115;
    ++frameNumber;
    QPixmap pixmap(filename);
    double centerX = target.x() + target.width() / 2;
    double centerY = target.y() + target.height() * 0.97;

    painter.translate(centerX, centerY);
    getLean();
    painter.rotate(theta);
    painter.translate(-centerX, -centerY);

    painter.drawPixmap(target, pixmap, source); // Draw flamethrower
//    painter.setPen(Qt::red); // Set the pen color/*
//    painter.drawRect(target); // Draw burn area

    painter.translate(centerX, centerY);
    painter.rotate(-theta);
    painter.translate(-centerX, -centerY);

    //_____________DUUUUCKS________________//
//    192.0, 194.0

    painter.setCompositionMode(QPainter::CompositionMode_SourceAtop);
    if (!initialized){
        std::array<int, 2> duck1 = {int(width() * 0.3), 0};
        duckPos.push_back(duck1);
        initialized = true;
    }
    animateDucks();

    QPoint duck;
    duck.setX(duckPos.at(0)[0]+height() / 10);
    duck.setY(duckPos.at(0)[1] * height() / stepsCount + height() / 10);

    bool collided = false;
    QPointF topLeft(target.topLeft().x()+width()*0.1,target.topLeft().y());
    QPointF topRight(target.topRight().x()-width()*0.1,target.topRight().y());
    QPointF bottomLeft(target.bottomLeft().x()+width()*0.1,target.bottomLeft().y());
    QPointF bottomRight(target.bottomRight().x()-width()*0.1,target.bottomRight().y());
//    topLeft.setX(topLeft.x()+50);
//    QPointF topRight = target.topRight();
//    QPointF bottomLeft = target.bottomLeft();
//    QPointF bottomRight = target.bottomRight();
    QPointF axis;
    axis.setX(centerX);
    axis.setY(centerY);
    rotate_point(&topLeft,theta,axis);
    rotate_point(&topRight,theta,axis);
    rotate_point(&bottomLeft,theta,axis);
    rotate_point(&bottomRight,theta,axis);

    QPointF points[4] = { topLeft,topRight,bottomRight,bottomLeft};
    QVector<QPointF> polygonPoints =  { topLeft,topRight,bottomRight,bottomLeft};
    painter.setPen(Qt::red); // Set the pen color/*
    painter.drawConvexPolygon(points, 4);

//    QRectF targetTest(topLeft,topRight,bottomLeft,bottomRight);    // 576x720

//    painter.drawRect(targetTest); // Draw collide area
    QPainterPath path;
    QPolygonF burnArea(polygonPoints);
    path.addPolygon(burnArea);
    collided = path.contains(duck);

    painter.drawEllipse(duck, 5 , 5);

    if (duckPos.at(0)[0] > topLeft.x() && duckPos.at(0)[0] < bottomRight.x()) {
        if (duckPos.at(0)[1] > topLeft.y() && duckPos.at(0)[1] < bottomRight.y()) {
            collided = true;
        }
    }

    for (int i = 0; i < duckPos.size(); i++){
        QRectF targetD(duckPos.at(i)[0], duckPos.at(i)[1] * height() / stepsCount, height() / 10, width() / 10);
        QRectF sourceD(0.0, 0.0, 192.0, 194.0);
        QString filenameD;
        if (collided){
            filenameD = QString("/home/pk/Wizualizacja_danych/assets/duck_burning.png");
        }
        else{
            filenameD = QString("/home/pk/Wizualizacja_danych/assets/duck.png");
        }
        QPixmap pixmapD(filenameD);

        painter.drawPixmap(targetD, pixmapD, sourceD); // Draw duck
    }
//    painter.end();
}

void MyWidget::rotate_point(QPointF *p, double angle, QPointF center) {
    double radians = angle * M_PI / 180.0;
    double cos_theta = std::cos(radians);
    double sin_theta = std::sin(radians);
    double xnew = (p->x() - center.x()) * cos_theta - (p->y() - center.y()) * sin_theta + center.x();
    double ynew = (p->x() - center.x()) * sin_theta + (p->y() - center.y()) * cos_theta + center.y();
    p->setX(xnew);
    p->setY(ynew);
}


void MyWidget::translate_point(QPointF *p, double transX, double transY) {
    double xnew = p->x() + transX;
    double ynew = p->x() + transY;
    p->setX(xnew);
    p->setX(ynew);
}


void MyWidget::animateDucks(){
    for (int i=0; i<duckPos.size(); i++){
        duckPos.at(i)[1]+=1;
        if (duckPos.at(i)[1]>stepsCount){
            duckPos.at(i)[1]=0;
        }
    }
}

void MyWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    // Perform necessary calculations or updates when the widget is resized
    // ...

    // Uncomment the following line if you want to maintain a fixed size for the widget
    //setFixedSize(event->size());
}

void MyWidget::startAnimation()
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MyWidget::animate);
    timer->start(50);
}

void MyWidget::getLean()
{
    // Calculate theta based on the resized dimensions if needed
     int ax = r.getAx();
//    int ax = 5000;
    theta = (-ax) / 364;
}

void MyWidget::animate()
{
    // Zmieniaj parametry rysowania, aby uzyskać animację
    update();
}
