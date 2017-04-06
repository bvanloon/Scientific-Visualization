#ifndef GLYPHBUILDER_H
#define GLYPHBUILDER_H

#include "grid/uniformgrid.h"
#include "utilities/gpudata.h"
#include "glyphs/glyphs.h"

class GlyphBuilder
{
   public:
      GlyphBuilder(const UniformGrid *grid,
                   Settings::sim::GlyphsType glyphThype,
                   Vertex::scalarGetter getTextureCoordinate,
                   Vertex::vectorGetter directionGetter);
      ~GlyphBuilder();

      GPUData getGPUData();

   protected:
      const UniformGrid *grid;

      Vertex::scalarGetter getTextureCoordinate;
      Vertex::vectorGetter getDirection;

   private:

      Settings::sim::GlyphsType glyphType;

      GPUData data;

      GPUData build(Settings::sim::GlyphsType glyphType) const;

      GPUData buildHedgeHogs() const;
      virtual GPUData buildHedgeHog(Vertex *vertex) const;

      GPUData buildTriangles() const;
      virtual GPUData buildTriangle(Vertex *vertex) const;

      GPUData buildAirplanes() const;
      virtual GPUData buildAirplane(Vertex *vertex) const;

      GPUData buildCones() const;
      virtual GPUData buildCone(Vertex *vertex) const;
};

#endif // GLYPHBUILDER_H
