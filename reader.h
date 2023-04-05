#ifndef READER_H
#define READER_H

#include <QApplication>
#include <QtCore>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

class Reader: public QObject
{
    Q_OBJECT
    int fd;
    QSocketNotifier *notifier;
//    static QByteArray buffer;
    char buffer[128];

public:
    explicit Reader(QObject *p = 0): QObject(p) {
        fd = open("/dev/hidraw2", O_RDONLY|O_NONBLOCK);
        if (fd >= 0) {
//                qInfo( "opened hidraw2" );
            notifier = new QSocketNotifier(fd, QSocketNotifier::Read, this);
            connect(notifier, SIGNAL(activated(int)), this, SLOT(handleRead()));
        }
        else
            qFatal("Could not open");

    }
public slots:
    void handleRead() {


        ssize_t count;
//        char block[128];
        notifier->setEnabled(false);
//        do {
            count = read(fd, buffer, 128);
//            this->buffer.append(block, count);
//        } while(count > 0);
//        qDebug() << "Read done, buffer size";
        this->interpretSerial();
        notifier->setEnabled(true);
    }
    void interpretSerial()  {
//        char buf[128];
        int nr;
//        qDebug() << "Read done, buffer size"<<sizeof(buffer);
//        while ( (nr=read(0, buffer, sizeof(buffer))) ) {
//            qDebug() << "Number: " <<nr;
//          if ( nr < 0 )
//            { perror("read(stdin)"); exit(1); }
//          if ( nr != 49 ) {
//            fprintf(stderr, "Unsupported report length %d."
//                " Wrong hidraw device or kernel<2.6.26 ?\n", nr);
//            exit(1);
//          }
          ax = buffer[41]<<8 | buffer[42];
          ay = buffer[43]<<8 | buffer[44];
          az = buffer[45]<<8 | buffer[46];
          printf("ax=%4d ay=%4d az=%4d\n", ax, ay, az);
          fflush(stdout);

        }
    int getAx(){
        return ax;
    }
    int getAy(){
        return ay;
    }
    int getAz(){
        return az;
    }
private:
    int ax, ay, az;

};

#endif
