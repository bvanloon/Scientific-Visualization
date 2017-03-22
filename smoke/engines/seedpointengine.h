#ifndef SEEDPOINTENGINE_H
#define SEEDPOINTENGINE_H

#include <QObject>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include "abstractengine.h"
#include "unused.h"

class SeedPointEngine : public AbstractEngine
{
   Q_OBJECT

   public:
      SeedPointEngine();
      void draw(Simulation *UNUSED(Simulation));

   private:
      int updateBuffers();
      static const int drawMode = GL_TRIANGLES;
};

#endif // SEEDPOINTENGINE_H
