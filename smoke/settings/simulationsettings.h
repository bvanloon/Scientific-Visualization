#ifndef SIMULATIONS_H
#define SIMULATIONS_H

#include <QObject>
#include <QSizeF>
#include <QMultiMap>
#include "settings.h"

class Settings::Simulation : public QObject
{
   Q_OBJECT
public:

   static const Simulation& instance();

   int dimension;
   float timestep;
   bool frozen;
   float force;
   QSizeF cellSize;

   const float fluidVelocityMagnitudeMinimum = 0.0f;
   const float fluidVelocityMagnitudeMaximum = 0.1f;

   const float forceFieldMagnitudeMinimum = 0.0f;
   const float forceFieldMagnitudeMaximum = 0.5f;

   const float simulationTimeStepMinimum = 0.35;
   const float simulationTimeStepMaximum = 0.45;


   QPair<float, float> getRange(Settings::visualization::ScalarVariable scalar) const;

signals:
   void valueRangeChanged(float minimum, float maximum);

   void forceChanged(float force);
   void toggleFrozen(bool frozen);
   void recomputeVertexPositions(QSize canvasSize, QSizeF cellSize);

public slots:
   void onDimensionChanged(int newDimension);
   void onForceChanged(float newForce);
   void onWindowResized(int width, int height);
   void onToggleFrozen();
   void onToggleFrozenKeyboard();
   void onTimeStepChanged(float value);

private:
   explicit Simulation(QObject *parent = 0);

   Simulation(Simulation const&)     = delete;
   void operator=(Simulation const&) = delete;

   QMultiMap<Settings::visualization::ScalarVariable, QPair<float, float>> scalarRanges;

   void updateRange(Settings::visualization::ScalarVariable scalar, float minimum, float maximum);

   void updateGridCellSize();
   void updateGridCellSize(int width, int height);
};

#endif // SIMULATIONS_H
