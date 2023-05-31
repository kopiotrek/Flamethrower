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

    int DUCK_COUNTER = 69;
    emit sendScore(DUCK_COUNTER);

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
        for(int i=0;i<2;i++){
            std::array<int, 4> newDuck;
            duckPos.push_back(newDuck);
            generateDuck(&i);
        }

//        std::array<int, 4> duck1 = {int(width() * 0.3), 0, 0, 2}; //x_coord, y_coord, is_burning, speed
//        duckPos.push_back(duck1);
        initialized = true;
        std::cout<<"Initialized "<<std::endl;
    }
    animateDucks();



    QPointF topLeft(target.topLeft().x()+width()*0.1,target.topLeft().y());
    QPointF topRight(target.topRight().x()-width()*0.1,target.topRight().y());
    QPointF bottomLeft(target.bottomLeft().x()+width()*0.1,target.bottomLeft().y());
    QPointF bottomRight(target.bottomRight().x()-width()*0.1,target.bottomRight().y());
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

    QPainterPath path;
    QPolygonF burnArea(polygonPoints);
    path.addPolygon(burnArea);

    QPoint duck;
    for(int i=0; i < duckPos.size(); i++){
        if (!duckPos.at(i)[2]){
            duck.setX(duckPos.at(i)[0]+height() / 20);
            duck.setY(duckPos.at(i)[1] * height() / stepsCount + height() / 10);
            duckPos.at(i)[2] = path.contains(duck);
        }
    }


    painter.drawEllipse(duck, 5 , 5);

    for (int i = 0; i < duckPos.size(); i++){
        QRectF targetD(duckPos.at(i)[0], duckPos.at(i)[1] * height() / stepsCount, height() / 10, width() / 10);
        QRectF sourceD(0.0, 0.0, 192.0, 194.0);
        QString filenameD;
        if (duckPos.at(i)[2]){
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
        duckPos.at(i)[1]+=duckPos.at(i)[3];
        if (duckPos.at(i)[1]>stepsCount){
            generateDuck(&i);
        }
    }
}

void MyWidget::generateDuck(int *i){
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr_x(width()*0.1, width()*0.9); // define the range
    std::uniform_int_distribution<> distr_y(-100, -10); // define the range
    std::uniform_int_distribution<> distr_v(1, 3); // define the range

    duckPos.at(*i)[0]=distr_x(gen); //x
    duckPos.at(*i)[1]=distr_y(gen); //y
    duckPos.at(*i)[2]=0; //not burning
    duckPos.at(*i)[3]=distr_v(gen); //speed
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
//     int ax = r.getAx();
//    int ax = 5000;
//    theta = (-ax) / 364;
    theta+=increment;
    if(theta>90){
        increment=-increment;
    }
    if(theta<-90){
        increment=-increment;
    }
}

void MyWidget::animate()
{
    // Zmieniaj parametry rysowania, aby uzyskać animację
    update();
}


