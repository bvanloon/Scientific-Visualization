#ifndef VECTORENGINE_H
#define VECTORENGINE_H

#include <QObject>
#include "abstractengine.h"
#include "grid/jittergrid.h"
#include "unused.h"

class GlyphEngine : public AbstractEngine {
   Q_OBJECT

   public:
      GlyphEngine(UniformGrid *simulationGrid);

      void draw();

   public slots:
      void onRecomputeVertexPositions(QSize canvasSize, QSizeF cellSize);

      void onGridDimensionChanged(int width, int UNUSED(height));

      void onReplaceGrid();

   signals:
      void cellSizeChanged(QSizeF newSize);

   private:

      UniformGrid *visualizationGrid;
      UniformGrid *simulationGrid;

      void connnectToSettings();
};

#endif // VECTORENGINE_H
