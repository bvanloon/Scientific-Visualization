#include "vertex.h"
#include "cell.h"

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
   }
   qDebug() << "Vertex::getVectorGetter: returning default vector getter.";
   return &Vertex::getFluidVelocity;
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

SimulationVertex::SimulationVertex(const QVector3D *position, double *vx, double *vy, double *fx, double *fy, double *rho) :
   StructuredGridVertex(position),
   vx(vx), vy(vy),
   fx(fx), fy(fy),
   rho(rho)
{}


QVector2D SimulationVertex::getFluidVelocity() const
{
   return QVector2D(*(vx), *(vy));
}

float SimulationVertex::getFluidVelocityMagnitude() const
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
   return QVector2D(*(fx), *(fy));
}

float SimulationVertex::getForceMagnitude() const
{
   return getForce().length();
}

float SimulationVertex::getFluidDensity() const
{
   return *rho;
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

float VisualizationVertex::getFluidVelocityMagnitude() const
{
   StructuredCell *cell = dynamic_cast<StructuredCell *>(containingCell);

   return cell->interpolateScalar(*position, &Vertex::getFluidVelocityMagnitude);
}

QVector2D VisualizationVertex::getFluidVelocityMagnitudeGradient() const
{
   qDebug() << "VisualizationVertex::getFluidVelocityMagnitudeGradient()";
   return QVector2D(0.0, 1.0);
}

QVector2D VisualizationVertex::getForce() const
{
   StructuredCell *cell = dynamic_cast<StructuredCell *>(containingCell);

   return cell->interpolate2DVector(*position, &Vertex::getForce);
}

float VisualizationVertex::getForceMagnitude() const
{
   StructuredCell *cell = dynamic_cast<StructuredCell *>(containingCell);

   return cell->interpolateScalar(*position, &Vertex::getForceMagnitude);
}

float VisualizationVertex::getFluidDensity() const
{
   StructuredCell *cell = dynamic_cast<StructuredCell *>(containingCell);

   return cell->interpolateScalar(*position, &Vertex::getFluidDensity);
}

QVector2D VisualizationVertex::getFluidDensityGradient() const
{
   qDebug() << "VisualizationVertex::getFluidDensityGradient not implemeneted";
   return QVector2D(1.0, 0.0);
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
