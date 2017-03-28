#ifndef GLYPHSLICEENGINE_H
#define GLYPHSLICEENGINE_H

#include <QObject>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include "abstractengine.h"
#include "grid/jittergrid.h"

#include "unused.h"
#include "glyphs/glyphsfactory.h"

class GlyphSliceEngine : public AbstractEngine {
   Q_OBJECT

   public:
      GlyphSliceEngine(UniformGrid *simulationGrid);

      virtual void draw(Simulation *UNUSED(Simulation));

   public slots:
      void onRecomputeVertexPositions(QSize canvasSize, QSizeF cellSize);

      void onGridDimensionChanged(int width, int UNUSED(height));

   signals:
      void cellSizeChanged(QSizeF newSize);

   private:
      virtual int updateBuffers();

      Grid *visualizationGrid;
      UniformGrid *simulationGrid;
      GlyphsFactory factory;
};

#endif // GLYPHSLICEENGINE_H
