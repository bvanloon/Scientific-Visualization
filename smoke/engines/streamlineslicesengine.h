#ifndef STREAMLINESLICESENGINE_H
#define STREAMLINESLICESENGINE_H

#include <QObject>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
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
      static const int drawMode = GL_LINES;

      GPUData buildStreamLines();

      GPUData buildStreamLine(QPointF seedPoint);

      virtual int updateBuffers();

      UniformGrid *grid;
};

#endif // STREAMLINESLICESENGINE_H
