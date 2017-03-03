#ifndef SMOKEENGINE_H
#define SMOKEENGINE_H

#include "abstractengine.h"

class SmokeEngine : public AbstractEngine
{
public:
    SmokeEngine();

    void draw(Simulation* simulation);


private:
    int updateBuffers(Simulation* simulation);


};


#endif // SMOKEENGINE_H
