#ifndef ABSTRACTSLICEENGINE_H
#define ABSTRACTSLICEENGINE_H

#include <QObject>
#include "abstractengine.h"

class AbstractSliceEngine : public AbstractEngine
{
   Q_OBJECT

   public:
      AbstractSliceEngine(AbstractEngine::lightModel lightModel);

      virtual void draw(Simulation *Simulation) = 0;

public slots:
      void onRotationChanged(int direction, int newAngle);

   private:
      virtual int updateBuffers(Simulation *simulation) = 0;
};

#endif // ABSTRACTSLICEENGINE_H
