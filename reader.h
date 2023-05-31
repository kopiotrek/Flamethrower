#ifndef READER_H
#define READER_H

#include <QApplication>
#include <QtCore>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

/**

@file reader.h
@brief Plik nagłówkowy klasy Reader.
Klasa Reader obsługuje odczytywanie danych ze specyficznego urządzenia HID i przetwarzanie ich na wartości liczbowe.
Urządzenie HID jest otwierane w konstruktorze klasy, a odczytywanie danych i ich interpretacja jest realizowana w funkcjach obsługujących zdarzenia.
Klasa Reader dziedziczy po QObject.
*/
class Reader: public QObject
{
    Q_OBJECT
    int fd;
    QSocketNotifier *notifier;
//    static QByteArray buffer;
    char buffer[128];

public:
    /**
    * @brief Konstruktor klasy Reader
    *
    * Tworzy obiekt klasy Reader, otwiera urządzenie HID i tworzy obiekt QSocketNotifier do monitorowania zdarzenia odczytu z urządzenia.
    *
    * @param[in] p wskaźnik na obiekt QObject, rodzica obiektu klasy Reader
    */
    explicit Reader(QObject *p = 0): QObject(p) {
        fd = open("/dev/dualshock3", O_RDONLY|O_NONBLOCK);
        if (fd >= 0) {
                qInfo( "opened Dualshock3" );
            notifier = new QSocketNotifier(fd, QSocketNotifier::Read, this);
            connect(notifier, SIGNAL(activated(int)), this, SLOT(handleRead()));
        }
        else
            qFatal("Could not open");

    }
public slots:
    /**
    * @brief Obsługa zdarzenia odczytu z urządzenia HID
    *
    * Odczytuje dane z urządzenia HID do bufora i wywołuje funkcję interpretSerial() do przetwarzania odczytanych danych.
    * Ustawia flagę enabled na false przed odczytem i na true po jego zakończeniu, aby umożliwić kolejne odczyty.
    */
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
    /**
     * @brief Przetwarzanie odczytanych danych
     *
     * Przetwarza odczytane dane ze specyficznego urządzenia HID na wartości osi x, y i z.
     */
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
    /**
     * @brief Pobieranie wartości osi x
     *
     * @return Wartość osi x
     */
    int getAx(){
        return ax;
    }
    /**
     * @brief Pobieranie wartości osi y
     *
     * @return Wartość osi y
     */
    int getAy(){
        return ay;
    }
    /**
     * @brief Pobieranie wartości osi z
     *
     * @return Wartość osi z
     */
    int getAz(){
        return az;
    }
private:
    int ax, ay, az;

};

#endif
