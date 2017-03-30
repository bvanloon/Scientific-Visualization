#include "vertex.h"
#include "cell.h"
#include "grid/simulationgrid.h"
#include "simulation/simulationdata.h"

Vertex::Vertex(const QVector3D *position) :
   position(position)
{}


Vertex::~Vertex()
{}


const QVector3D *Vertex::getPosition() const
{
   return this->position;
}

Vertex::scalarGetter Vertex::getScalarGetter(Settings::sim::Scalar scalar)
{
   switch (scalar)
   {
   case Settings::sim::fluidDensity:
      return &Vertex::getFluidDensity;

   case Settings::sim::fluidVelocityMagnitude:
      return &Vertex::getFluidVelocityMagnitude;

   case Settings::sim::forceFieldMagnitude:
      return &Vertex::getForceMagnitude;

   default:
      qDebug() << "Vertex::getScalarGetter(): Current scalar is not supported. Using default getFluidDensity";
      return &Vertex::getFluidDensity;
   }
}

Vertex::vectorGetter Vertex::getVectorGetter(Settings::sim::Vector vector)
{
   switch (vector)
   {
   case Settings::sim::fluidVelocity:
      return &Vertex::getFluidVelocity;

   case Settings::sim::force:
      return &Vertex::getForce;

   case Settings::sim::fluidDensityGradient:
      return &Vertex::getFluidDensityGradient;

   case Settings::sim::fluidVelocityMagnitudeGradient:
      return &Vertex::getFluidVelocityMagnitudeGradient;

   default:
      qDebug() << "Vertex::getVectorGetter(): Current vector is not supported. Using default fluidVelocity ";
      return &Vertex::getFluidVelocity;
   }
}

QDebug operator<<(QDebug stream, const Vertex& vertex)
{
   stream << "Vertex ["
          << " position: "
          << *vertex.position
          << "]";

   return stream;
}

QDebug operator<<(QDebug stream, Vertex *vertex)
{
   stream << *vertex;
   return stream;
}

SimulationVertex::SimulationVertex(const QVector3D *position, double *vx, double *vy, double *fx, double *fy, double *rho, size_t idx, SimulationGrid *grid) :
   StructuredGridVertex(position),
   vx(vx), vy(vy),
   fx(fx), fy(fy),
   rho(rho),
   idx(idx),
   containingGrid(grid)
{}

QVector2D SimulationVertex::getFluidVelocity() const
{
   return containingGrid->getData()->getFluidVelocityAt(this->idx);
}

double SimulationVertex::getFluidVelocityMagnitude() const
{
   return getFluidVelocity().length();
}

QVector2D SimulationVertex::getFluidVelocityMagnitudeGradient() const
{
   std::logic_error("SimulationVertex::getFluidVelocityMagnitudeGradient is not implemented.");
   return QVector2D();
}

QVector2D SimulationVertex::getForce() const
{
   return containingGrid->getData()->getForceAt(this->idx);
}

double SimulationVertex::getForceMagnitude() const
{
   return getForce().length();
}

double SimulationVertex::getFluidDensity() const
{
   return containingGrid->getData()->getDensityAt(this->idx);
}

QVector2D SimulationVertex::getFluidDensityGradient() const
{
   std::logic_error("SimulationVertex::getFluidDensityGradient is not implemented.");
   return QVector2D();
}

QDebug operator<<(QDebug stream, const SimulationVertex& vertex)
{
   stream << "SimulationVertex ["
          << " position: " << *vertex.position
          << " (vx, vy): (" << *vertex.vx << ", " << *vertex.vy << ")"
          << " (fx, fy): (" << *vertex.fx << ", " << *vertex.fy << ")"
          << " (rho): (" << *vertex.rho << ")"
          << "]";
   return stream;
}

QDebug operator<<(QDebug stream, SimulationVertex *vertex)
{
   stream << *vertex;
   return stream;
}

QDebug operator<<(QDebug stream, const VisualizationVertex& vertex)
{
   stream << "VisualizationVertex ["
          << " position: " << *vertex.position
          << "]";
   return stream;
}

QDebug operator<<(QDebug stream, VisualizationVertex *vertex)
{
   stream << *vertex;
   return stream;
}

VisualizationVertex::VisualizationVertex(const QVector3D *position, Cell *cell) :
   StructuredGridVertex(position),
   containingCell(cell)
{}


QVector2D VisualizationVertex::getFluidVelocity() const
{
   StructuredCell *cell = dynamic_cast<StructuredCell *>(containingCell);

   return cell->interpolate2DVector(*position, &Vertex::getFluidVelocity);
}

double VisualizationVertex::getFluidVelocityMagnitude() const
{
   StructuredCell *cell = dynamic_cast<StructuredCell *>(containingCell);

   return cell->interpolateScalar(*position, &Vertex::getFluidVelocityMagnitude);
}

QVector2D VisualizationVertex::getFluidVelocityMagnitudeGradient() const
{
   StructuredCell *cell = dynamic_cast<StructuredCell *>(containingCell);

   return cell->computeGradient(*position, &Vertex::getFluidVelocityMagnitude);
}

QVector2D VisualizationVertex::getForce() const
{
   StructuredCell *cell = dynamic_cast<StructuredCell *>(containingCell);

   return cell->interpolate2DVector(*position, &Vertex::getForce);
}

double VisualizationVertex::getForceMagnitude() const
{
   StructuredCell *cell = dynamic_cast<StructuredCell *>(containingCell);

   return cell->interpolateScalar(*position, &Vertex::getForceMagnitude);
}

double VisualizationVertex::getFluidDensity() const
{
   StructuredCell *cell = dynamic_cast<StructuredCell *>(containingCell);

   return cell->interpolateScalar(*position, &Vertex::getFluidDensity);
}

QVector2D VisualizationVertex::getFluidDensityGradient() const
{
   StructuredCell *cell = dynamic_cast<StructuredCell *>(containingCell);

   return cell->computeGradient(*position, &Vertex::getFluidDensity);
}

StructuredGridVertex::StructuredGridVertex(const QVector3D *position) :
   Vertex(position)
{}


Cell *StructuredGridVertex::getLowerRightCell() const
{
   return lowerRightCell;
}

void StructuredGridVertex::setLowerRightCell(Cell *value)
{
   lowerRightCell = value;
}

bool StructuredGridVertex::hasLowerRightCell()
{
   return lowerRightCell != nullptr;
}
