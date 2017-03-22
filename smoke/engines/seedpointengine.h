#ifndef SEEDPOINTENGINE_H
#define SEEDPOINTENGINE_H

#include "abstractengine.h"
#include "unused.h"

class SeedPointEngine : public AbstractEngine
{
   Q_OBJECT

   public:
      SeedPointEngine();

      void draw(Simulation *UNUSED(simulation));

   private:
      int updateBuffers();

      static const int drawMode = GL_TRIANGLES;
};

#endif // SEEDPOINTENGINE_H
