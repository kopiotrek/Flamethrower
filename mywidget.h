/**

@file mywidget.h
@brief Plik nagłówkowy klasy MyWidget - widgeta służącego do wyświetlania animacji.
Klasa MyWidget dziedziczy po QWidget i służy do wyświetlania animacji na widgetcie.
Widget wyświetla kolejne klatki animacji, które są zapisane jako obrazy png.
Animacja jest obracana o kąt wyznaczony przez wartość odczytaną z obiektu klasy Reader.
*/

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
#include <vector>
#include <cmath>
#include "reader.h"


class MyWidget : public QWidget
{
    Q_OBJECT;
    Reader r;
    std::vector<std::array<int, 2>> duckPos;
    bool initialized = false;
public:
    /**
    * @brief Konstruktor klasy MyWidget.
    *
    * Konstruktor tworzy widget o stałym rozmiarze 500x500 pikseli.
    *
    * @param parent Wskaźnik na obiekt rodzica, domyślnie nullptr.
    */
    explicit MyWidget(QWidget *parent = nullptr);

protected:
    /**
    * @brief Metoda rysująca.
    *
    * Metoda rysująca, która jest wywoływana za każdym razem, gdy widget wymaga odświeżenia.
    * Wewnątrz funkcji rysującej ustawiany jest kolor tła oraz rysowany jest obraz animacji,
    * który jest obracany o kąt wyznaczony przez funkcję getLean().
    *
    * @param event Zdarzenie rysowania, domyślnie nullptr.
    */
    void paintEvent(QPaintEvent *event) override;
    double theta = 0;
    int frameNumber = 0;
    bool startup = false;
    int stepsCount = 200;

private:
    void resizeEvent(QResizeEvent *event);
    /**
    * @brief Metoda rozpoczynająca animację.
    *
    * Metoda tworzy timer, który co określony czas wywołuje funkcję animate().
    */
    void startAnimation();
    /**
     * @brief Metoda animująca.
     *
     * Metoda zmienia parametry rysowania w celu uzyskania animacji.
     * Metoda jest wywoływana za każdym razem, gdy timer wyzwoli sygnał timeout().
     */
    void animate();
    /**
     * @brief Metoda obliczająca kąt obrotu animacji.
     *
     * Metoda oblicza kąt obrotu animacji na podstawie wartości odczytanej z obiektu klasy Reader.
     * Obliczony kąt przypisywany jest do zmiennej theta.
     */
    void getLean();

    void animateDucks();

    void rotate_point(QPointF *p, double angle, QPointF center);

    void translate_point(QPointF *p, double transX, double transY);
};

#endif // MYWIDGET_H
