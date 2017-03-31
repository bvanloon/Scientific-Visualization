#ifndef STREAMLINESLICESENGINE_H
#define STREAMLINESLICESENGINE_H

#include <QObject>
#include "abstractsliceengine.h"
#include "unused.h"

class StreamLineSlicesEngine : public AbstractSliceEngine
{
   Q_OBJECT

   public:
      StreamLineSlicesEngine(UniformGrid *simulationGrid);

      virtual void draw(Simulation *simulation);

   public slots:

   signals:

   private:
      static const int drawMode = GL_LINES;

      GPUData buildStreamLines();

      GPUData buildStreamLine(QPointF seedPoint);

      int fillBuffers(Simulation *UNUSED(Simulation));

      UniformGrid *grid;
};

#endif // STREAMLINESLICESENGINE_H
