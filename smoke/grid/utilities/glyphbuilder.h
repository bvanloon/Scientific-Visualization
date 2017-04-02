#ifndef GLYPHBUILDER_H
#define GLYPHBUILDER_H

#include "grid/uniformgrid.h"
#include "utilities/gpudata.h"

class GlyphBuilder
{
   public:
      GlyphBuilder(UniformGrid *grid,
                   Settings::sim::GlyphsType glyphThype,
                   Vertex::scalarGetter getTextureCoordinate,
                   Vertex::vectorGetter directionGetter);
      ~GlyphBuilder();

      GPUData getData() const;

private:
      UniformGrid *grid;

      Vertex::scalarGetter getTextureCoordinate;
      Vertex::vectorGetter getDirection;

      GPUData data;

      GPUData build(Settings::sim::GlyphsType glyphType);

      GPUData buildHedgeHodges();
      GPUData buildTriangles();
      GPUData buildTriangle(Vertex* vertex);
      GPUData buildAirplanes();
      GPUData buildCones();
};

#endif // GLYPHBUILDER_H
