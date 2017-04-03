#include "translucentsmokebuilder.h"

TranslucentSmokeBuilder::TranslucentSmokeBuilder(SimulationGrid *grid, Vertex::scalarGetter textureGetter) :
   AbstractTranslucentBuilder(),
   SmokeBuilder(grid, textureGetter)
{
}
