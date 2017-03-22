#ifndef SEEDPOINTENGINE_H
#define SEEDPOINTENGINE_H

#include "abstractengine.h"

class SeedPointEngine : public AbstractEngine
{
   Q_OBJECT

   public:
      SeedPointEngine();

      void draw(Simulation *Simulation);

   private:
      int updateBuffers(Simulation *simulation);

      static const int drawMode = GL_TRIANGLES;
};

#endif // SEEDPOINTENGINE_H
