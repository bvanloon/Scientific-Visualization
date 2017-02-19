#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

#include <fftw.h>

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0);
    ~Settings();

    class Canvas {

        public:
            int width;
            int height;

            Canvas()
                :
                width(-1),
                height(-1)
            {}
    };

    class Visualization {
        public:
            float vecScale;

            Visualization():
                vecScale(1000)
            {}
    };

    Canvas *canvas;
    Visualization *visualization;

public slots:
    void onWindowResized(int width, int height);
};

#endif // SETTINGS_H
