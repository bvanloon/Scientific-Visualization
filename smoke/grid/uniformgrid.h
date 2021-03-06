#ifndef UNIFORMGRID_H
#define UNIFORMGRID_H

#include "grid/grid.h"
#include <QSizeF>
#include "simulation/simulationrealization.h"
#include <QRectF>
#include "unused.h"

class SimulationGrid;

class UniformGrid : public Grid
{
   public:
      QVector<QVector3D> const& getVertexPositions() const;

      QSizeF const& getPadding() const;

      QSizeF getCellSize() const;

      Triangulation getTriangulation() const;

      int getDimension() const;

      bool inGridArea(QVector3D position) const;

      StructuredCell *findCellContaining(QVector3D position) const;

      virtual void changeGridArea(QSizeF UNUSED(newArea));
      virtual void changeGridArea(QSizeF newArea, QSizeF padding);

      static UniformGrid *createVisualizationGrid(int dimension, QSizeF size, UniformGrid *simulationGrid);

   protected:
      UniformGrid(int dimension, bool hasPadding);
      UniformGrid(int dimension, QSizeF areaSize, QSizeF padding);
      UniformGrid(int dimension, QSizeF cellSize, bool hasPadding, QSizeF padding);

      static void createVertices(UniformGrid *visualizationGrid, UniformGrid *simulationGrid);

      static void createCells(UniformGrid *grid);

      static void createTriangulation(UniformGrid *grid);

      virtual QVector3D computeVertexPosition(int i, int j);

      QVector3D bindToGrid(QVector3D position);

      int to1Dindex(int x, int y) const;

      int to1Dindex(Index2D idx) const;

      Vertex *getVertexAt(int x, int y) const;

      QRectF computeCoveredArea(QSizeF padding, QSizeF cellSize);

      int dimension;
      QSizeF cellSize;
      QSizeF padding;
      QRectF coveredArea;

      Triangulation triangulation;

   private:

      void recomputeVertexPositions(QSizeF oldCellSize, QSizeF newCellSize);

      QSizeF computeCellSize(QSizeF area, QSizeF padding);

      QPair<int, int> findUpperLeftOfContainingCell(QVector3D position) const;
};

#endif // UNIFORMGRID_H
