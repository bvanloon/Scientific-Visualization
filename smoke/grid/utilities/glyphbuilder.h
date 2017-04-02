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

      GPUData buildHedgeHogs();
      GPUData buildHedgeHog(Vertex* vertex);

      GPUData buildTriangles();
      GPUData buildTriangle(Vertex* vertex);

      GPUData buildAirplanes();
      GPUData buildAirplane(Vertex* vertex);

      GPUData buildCones();
      GPUData buildCone(Vertex* vertex);
};

#endif // GLYPHBUILDER_H
