#ifndef SIMULATIONGRID_H
#define SIMULATIONGRID_H

#include "grid/uniformgrid.h"
#include "simulation/simulationdata.h"

class SimulationGrid : public UniformGrid
{
   public:
      SimulationGrid(int dimension, QSizeF areaSize, SimulationData *data);
      SimulationData getData() const;

      void setData(const SimulationData& value);

   private:
      SimulationData *data;
};


#endif // SIMULATIONGRID_H
