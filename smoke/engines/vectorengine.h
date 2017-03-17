#ifndef VECTORENGINE_H
#define VECTORENGINE_H

#include <QObject>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include "abstractengine.h"
#include "unused.h"
#include "glyphs/glyphsfactory.h"

class VectorEngine : public AbstractEngine {
   Q_OBJECT

   public:
      VectorEngine(UniformGrid *simulationGrid);

      void draw(Simulation *UNUSED(simulation));

   public slots:
      void onRecomputeVertexPositions(QSize canvasSize, QSizeF cellSize);

      void onGridDimensionChanged(int width, int UNUSED(height));

   signals:
      void cellSizeChanged(QSizeF newSize);

   private:
      int updateBuffers();

      Grid *visualizationGrid;
      UniformGrid *simulationGrid;
      GlyphsFactory factory;
};

#endif // VECTORENGINE_H
