#include "grid/vertex.h"

StateVertex::StateVertex(SimulationVertex *simulationVertex) :
   StructuredGridVertex(simulationVertex->position),
   vx(*simulationVertex->vx), vy(*simulationVertex->vy),
   fx(*simulationVertex->fx), fy(*simulationVertex->fy),
   rho(*simulationVertex->rho)
{}

StateVertex::~StateVertex()
{}

QDebug operator<<(QDebug stream, const StateVertex& vertex)
{
   stream << "StateVertex ["
          << " position: " << *vertex.position
          << " (vx, vy): (" << vertex.vx << ", " << vertex.vy << ")"
          << " (fx, fy): (" << vertex.fx << ", " << vertex.fy << ")"
          << " (rho): (" << vertex.rho << ")"
          << "]";
   return stream;
}

QDebug operator<<(QDebug stream, StateVertex *vertex)
{
   stream << *vertex;
   return stream;
}

QVector2D StateVertex::getFluidVelocity() const
{
   return QVector2D(vx, vy);
}

float StateVertex::getFluidVelocityMagnitude() const
{
   return getFluidVelocity().length();
}

QVector2D StateVertex::getFluidVelocityMagnitudeGradient() const
{
   std::logic_error("StateVertex::getFluidVelocityMagnitudeGradient is not implemented.");
   return QVector2D();
}

QVector2D StateVertex::getForce() const
{
    return QVector2D(fx, fy);
}

float StateVertex::getForceMagnitude() const
{
    return getForce().length();
}

float StateVertex::getFluidDensity() const
{
   return rho;
}

QVector2D StateVertex::getFluidDensityGradient() const
{
   std::logic_error("StateVertex::getFluidDensityGradient is not implemented.");
   return QVector2D();
}
