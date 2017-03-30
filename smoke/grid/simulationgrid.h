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

      void addVertices();
      void addVertex(int x, int y);
      const QVector3D* addVertexPosition(int idx, QVector3D position);
};


#endif // SIMULATIONGRID_H
