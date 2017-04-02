#ifndef GLYPHBUILDER_H
#define GLYPHBUILDER_H

#include "grid/uniformgrid.h"
#include "utilities/gpudata.h"

class GlyphBuilder
{
   public:
      GlyphBuilder(UniformGrid *grid, Settings::sim::GlyphsType glyphThype);
      ~GlyphBuilder();

   private:
      UniformGrid *grid;
      GPUData* data;

      GPUData *build(Settings::sim::GlyphsType glyphType);
      GPUData *buildHedgeHodgs();
      GPUData *buildTriangles();
      GPUData *buildAirplanes();
      GPUData *buildCones();
};

#endif // GLYPHBUILDER_H
