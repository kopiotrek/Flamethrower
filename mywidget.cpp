#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(1920, 1080);
    startAnimation();
}

void MyWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);


    // Fill the background with black color
    painter.fillRect(rect(), Qt::black);

    QRectF target(665.0, 0.0, 576.0, 720.0);
    QRectF source(0.0, 0.0, 576.0, 720.0);
    QString filename = QString("/home/pk/Wizualizacja_danych/assets/side_frames/frame_%1.png")
            .arg(QString::number(frameNumber).rightJustified(3, '0')); // format frame number with leading zeros


    if (frameNumber > 100)
        startup = true;
    if (startup == true && frameNumber == 130)
            frameNumber = 115;
     ++frameNumber;
     QPixmap pixmap(filename);



    double x = 960, y = 720;

    painter.translate(x,y);
    getLean();
    painter.rotate(theta);
    painter.translate(-x,-y);
    painter.drawPixmap(target, pixmap, source);
}



void MyWidget::startAnimation()
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MyWidget::animate);
    timer->start(50);
    qInfo( "startAnimation" );
}

void MyWidget::getLean(){
    int ax=r.getAx();

    theta=(-ax)/364;
}

void MyWidget::animate()
{
    // Zmieniaj parametry rysowania, aby uzyskać animację
    update();
}
