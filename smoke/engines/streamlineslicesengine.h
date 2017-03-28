#ifndef STREAMLINESLICESENGINE_H
#define STREAMLINESLICESENGINE_H

#include <QObject>
#include "abstractengine.h"
#include "unused.h"

class StreamLineSlicesEngine : public AbstractEngine
{
   Q_OBJECT

   public:
      StreamLineSlicesEngine(UniformGrid *simulationGrid);

      virtual void draw(Simulation *UNUSED(simulation));

   public slots:

   signals:

   private:
      static const int drawMode = GL_LINES;

      GPUData buildStreamLines();

      GPUData buildStreamLine(QPointF seedPoint);

      virtual int updateBuffers();

      UniformGrid *grid;
};

#endif // STREAMLINESLICESENGINE_H
