//#include "mainwindow.h"

//#include <QApplication>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
//}
#include <QApplication>
#include <QtCore>
#include <QMovie>
#include <QLabel>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "mywidget.h"



int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MyWidget w;
    w.show();
//    QLabel label;
//        QMovie *movie = new QMovie("/home/pk/Wizualizacja_danych/assets/Flame_Thrower_Blast_Side.gif");
//        label.setMovie(movie);
//        movie->start();

//        label.show();
    return app.exec();

}
#include "main.moc"
