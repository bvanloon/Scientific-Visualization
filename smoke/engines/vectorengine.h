#ifndef VECTORENGINE_H
#define VECTORENGINE_H

#include <QObject>
#include "abstractengine.h"
#include "grid/jittergrid.h"

#include "unused.h"
#include "glyphs/glyphsfactory.h"

class VectorEngine : public AbstractEngine {
   Q_OBJECT

   public:
      VectorEngine(UniformGrid *simulationGrid);

      void draw();

   public slots:
      void onRecomputeVertexPositions(QSize canvasSize, QSizeF cellSize);

      void onGridDimensionChanged(int width, int UNUSED(height));

   signals:
      void cellSizeChanged(QSizeF newSize);

   private:
      int fillBuffers();

      Grid *visualizationGrid;
      UniformGrid *simulationGrid;
      GlyphsFactory factory;
};

#endif // VECTORENGINE_H
