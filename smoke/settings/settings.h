#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0);
    ~Settings();

    friend QDebug operator<<(QDebug stream, const Settings &settings);

    class Simulation {
        public:
            int dimension;

            friend QDebug operator<<(QDebug stream, const Settings::Simulation &simulation);

            Simulation() :
                dimension(50)
            {}
    };

    class Canvas {

        public:
            int width;
            int height;

            friend QDebug operator<<(QDebug stream, const Settings::Canvas &canvas);

            Canvas() :
                width(-1),
                height(-1)
            {}
    };

    Simulation *simulation;
    Canvas *canvas;

signals:

public slots:
};

#endif // SETTINGS_H
