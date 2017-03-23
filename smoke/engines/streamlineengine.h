#ifndef STREAMLINEENGINE_H
#define STREAMLINEENGINE_H
#include <QObject>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include "abstractengine.h"
#include "unused.h"

class StreamLineEngine : public AbstractEngine {
   Q_OBJECT

   public:
      StreamLineEngine(UniformGrid *simulationGrid);

      void draw(Simulation *UNUSED(simulation));

   public slots:

   signals:

   private:
      static const int drawMode = GL_LINES;

      int updateBuffers();

      UniformGrid *grid;
};

#endif // STREAMLINEENGINE_H
