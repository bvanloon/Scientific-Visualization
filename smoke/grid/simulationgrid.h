#ifndef SIMULATIONGRID_H
#define SIMULATIONGRID_H

#include <QMatrix4x4>
#include "grid/uniformgrid.h"
#include "simulation/simulationdata.h"

class SimulationGrid : public UniformGrid
{
   public:
      SimulationGrid(int dimension, QSizeF areaSize, SimulationData *data);
      ~SimulationGrid();

      SimulationData getData() const;

      void setData(const SimulationData& value);

      virtual void changeGridArea(QSizeF newArea);

   private:
      SimulationData *data;

      void createVertices();
      void createVertex(int x, int y);

      const QVector3D *addVertexPosition(int idx, QVector3D position);

      void createCells();
      void createCell(int x, int y);

      void createTriangulation();

      QSizeF computeCellSize(QSizeF gridArea);
      QMatrix4x4 computeScaleMatrix(QSizeF oldCellSize, QSizeF newCellSize);

      void transform(QMatrix4x4 transformation);
};

#endif // SIMULATIONGRID_H
