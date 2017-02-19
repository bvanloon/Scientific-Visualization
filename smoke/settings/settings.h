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

    class Visualization {
        public:
//            float vecScale;

            Visualization()
//                :
//                vecScale(1000)
            {}
    };

    Visualization *visualization;
};

#endif // SETTINGS_H
