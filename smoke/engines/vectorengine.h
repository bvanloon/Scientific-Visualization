#ifndef VECTORENGINE_H
#define VECTORENGINE_H

#include <QObject>
#include "abstractengine.h"

#include "glyphs/glyphsfactory.h"
class VectorEngine : public AbstractEngine {
   Q_OBJECT

public:

   VectorEngine(UniformGrid *simulationGrid);

   void draw(Simulation *simulation);

public slots:

   void onRecomputeVertexPositions(QSize canvasSize, QSizeF cellSize);
   void onGridDimensionChanged(int width, int height);

private:

   int updateBuffers();

   Grid *visualizationGrid;
   UniformGrid* simulationGrid;
};

#endif // VECTORENGINE_H
