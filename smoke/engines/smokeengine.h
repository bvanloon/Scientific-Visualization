#ifndef SMOKEENGINE_H
#define SMOKEENGINE_H

#include "abstractengine.h"

class SmokeEngine : public AbstractEngine
{
public:
    SmokeEngine();

    void draw(Simulation* simulation);

    void setTexture(QImage image);
    void setColorMapValueRange(float min, float max);
    void setColorMapClampRange(float startClamp, float endClamp);
    void setColorMapClampingTo(bool clampingOn);

private:
    int updateBuffers(Simulation* simulation);


};


#endif // SMOKEENGINE_H
