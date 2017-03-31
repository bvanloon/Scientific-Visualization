#ifndef STREAMLINEENGINE_H
#define STREAMLINEENGINE_H

#include <QObject>
#include "abstractengine.h"
#include "unused.h"

class StreamLineEngine : public AbstractEngine {
   Q_OBJECT

   public:
      StreamLineEngine(UniformGrid *simulationGrid);

      virtual void draw(Simulation *UNUSED(simulation));

   public slots:

   signals:

   private:
      static const int drawMode = GL_LINES;

      GPUData buildStreamLines();

      GPUData buildStreamLine(QPointF seedPoint);

      int fillBuffers();

      UniformGrid *grid;
};

#endif // STREAMLINEENGINE_H
