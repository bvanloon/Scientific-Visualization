#ifndef SMOKE_H
#define SMOKE_H

#include <QObject>

class Simulation : public QObject
{
    Q_OBJECT
public:
    explicit Simulation(QObject *parent = 0);

signals:

public slots:
};

#endif // SMOKE_H
