#ifndef GLYPHSLICEENGINE_H
#define GLYPHSLICEENGINE_H

#include "abstractsliceengine.h"
#include "unused.h"
#include "grid/jittergrid.h"

class GlyphSliceEngine : public AbstractSliceEngine {
   Q_OBJECT

   public:
      GlyphSliceEngine(SimulationGrid *simulationGrid);

   public slots:
      void onRecomputeVertexPositions(QSize canvasSize, QSizeF cellSize);

      void onGridDimensionChanged(int width, int UNUSED(height));

   signals:
      void cellSizeChanged(QSizeF newSize);

   protected:
      void updateCache();

   private:

      UniformGrid *visualizationGrid;
      SimulationGrid *simulationGrid;

      void connectToSettings();
};

#endif // GLYPHSLICEENGINE_H
