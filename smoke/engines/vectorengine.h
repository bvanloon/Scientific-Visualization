#ifndef VECTORENGINE_H
#define VECTORENGINE_H

#include <QObject>
#include "abstractengine.h"

class VectorEngine : public AbstractEngine
{
    Q_OBJECT

public:
    VectorEngine();

    void draw(Simulation* simulation);

public slots:
    void onGridDimensionChanged(int width, int height);

private:
    int updateBuffers(Simulation* simulation);

};

#endif // VECTORENGINE_H
