#ifndef GLYPHSLICEENGINE_H
#define GLYPHSLICEENGINE_H

#include "abstractsliceengine.h"
#include "unused.h"
#include "grid/jittergrid.h"
#include "glyphs/glyphsfactory.h"

class GlyphSliceEngine : public AbstractSliceEngine {
   Q_OBJECT

   public:
      GlyphSliceEngine(UniformGrid *simulationGrid);

      void draw();

   public slots:
      void onRecomputeVertexPositions(QSize canvasSize, QSizeF cellSize);

      void onGridDimensionChanged(int width, int UNUSED(height));

   signals:
      void cellSizeChanged(QSizeF newSize);

   protected:

      void updateCache();

   private:
      int fillBuffers();

      Grid *visualizationGrid;
      UniformGrid *simulationGrid;
      GlyphsFactory factory;
};

#endif // GLYPHSLICEENGINE_H
