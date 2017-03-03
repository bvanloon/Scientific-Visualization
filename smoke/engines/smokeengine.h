#ifndef SMOKEENGINE_H
#define SMOKEENGINE_H

#include "abstractengine.h"

class SmokeEngine : public AbstractEngine
{
public:
    SmokeEngine();

    void draw(Simulation* simulation);

public slots:
    void onValueRangeChanged(float min, float max);

private:
    int updateBuffers(Simulation* simulation);


};


#endif // SMOKEENGINE_H
