#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0);
    ~Settings();


    class Simulation {
        public:
            int dimension;

            Simulation() :
                dimension(50)
            {}
    };

    class Canvas {

        public:
            int width;
            int height;

            Canvas() :
                width(-1),
                height(-1)
            {}
    };

    Simulation *simulation;
    Canvas *canvas;

signals:

public slots:
    void onWindowResized(int width, int height);
};

#endif // SETTINGS_H
