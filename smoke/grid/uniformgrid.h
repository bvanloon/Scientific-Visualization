#ifndef UNIFORMGRID_H
#define UNIFORMGRID_H

#include "grid/grid.h"
#include <QSizeF>
#include "simulation/simulationrealization.h"

class UniformGrid : public Grid
{
   public:
      QVector<QVector3D> const& getVertexPositions() const;

      Triangulation getTriangulation() const;

      virtual void changeGridArea(QSizeF newArea);

      virtual void changeGridArea(QSizeF newArea, QSizeF padding);

      static UniformGrid *createSimulationGrid(int dimension, QSizeF size, SimulationRealization *simulation);

      static UniformGrid *createVisualizationGrid(int dimension, QSizeF size, UniformGrid *simulationGrid);

      QSizeF const& getPadding() const;

      QSizeF getCellSize() const;

      int getDimension() const;

   protected:
      UniformGrid(int dimension, QSizeF areaSize, bool hasPadding);
      UniformGrid(int dimension, QSizeF areaSize, QSizeF padding);

      static void createVertices(UniformGrid *grid, SimulationRealization *simulation);

      static void createVertices(UniformGrid *visualizationGrid, UniformGrid *simulationGrid);

      static void createCells(UniformGrid *grid);

      virtual QVector3D computeVertexPosition(int i, int j);
   private:
      int dimension;
      QSizeF cellSize;
      QSizeF padding;

      void recomputeVertexPositions();

      QSizeF computeCellSize(QSizeF area);

      QSizeF computeCellSize(QSizeF area, QSizeF padding);

      int to1Dindex(int x, int y) const;

      Cell *findCellContaining(QVector3D position);

      QVector3D computeVertexPosition(int i, int j);

      Vertex *getVertexAt(int x, int y) const;

      QPair<int, int> findUpperLeftOfContainingCell(QVector3D position);
};

#endif // UNIFORMGRID_H
