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

    class Grid {
        public:
            fftw_real cellWidth;
            fftw_real cellHeight;

            Grid() :
                cellWidth(-1),
                cellHeight(-1)
            {}
    };

    class Visualization {
        public:
            float vecScale;

            Visualization():
                vecScale(1000)
            {}
    };

    Simulation *simulation;
    Canvas *canvas;
    Grid *grid;
    Visualization *visualization;

signals:

public slots:
    void onWindowResized(int width, int height);
    void onDimensionChanged(int newDimension);

private:
    void updateGridCellSize();
};

#endif // SETTINGS_H
