#include "mainwindow.h"

//#include <QApplication>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
//}
#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QtCore>
#include <QMovie>
#include <QLabel>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "mywidget.h"
#include "scorewidget.h"



int main(int argc, char **argv)
{
    QApplication app(argc, argv);
        MainWindow w;
        w.show();
        QDialog dialog;
        dialog.setWindowTitle("Podłączenie pada");

        QLabel label(&dialog);
        label.setPixmap(QPixmap("/home/pk/Wizualizacja_danych/assets/dualshock3_200x100.png"));
        label.setGeometry(50, 50, 200, 200);

        QLabel message(&dialog);
        message.setText("Proszę podłączyć kontroler");
        message.setGeometry(50, 260, 200, 20);

        QPushButton button("Zamknij", &dialog);
        button.setGeometry(50, 290, 200, 30);
        QObject::connect(&button, &QPushButton::clicked, &dialog, &QDialog::accept);

        dialog.show();

    return app.exec();

}
#include "main.moc"
