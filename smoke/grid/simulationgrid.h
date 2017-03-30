#ifndef SIMULATIONGRID_H
#define SIMULATIONGRID_H

#include "grid/uniformgrid.h"
#include "simulation/simulationdata.h"

class SimulationGrid : public UniformGrid
{
   public:
      SimulationGrid(int dimension, QSizeF areaSize, SimulationData *data);
      ~SimulationGrid();

      SimulationData getData() const;

      void setData(const SimulationData& value);

   private:
      SimulationData *data;

      void createVertices();
      void createVertex(int x, int y);

      const QVector3D *addVertexPosition(int idx, QVector3D position);

      void createCells();
      void createCell(int x, int y);

      void createTriangulation();
};


#endif // SIMULATIONGRID_H
