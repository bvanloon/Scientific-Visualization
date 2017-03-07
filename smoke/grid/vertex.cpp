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
