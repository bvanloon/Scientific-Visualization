#ifndef STREAMOBJECT_H
#define STREAMOBJECT_H

#include <QObject>
#include <QSizeF>
#include "grid/vertex.h"

class StreamObject : public QObject {
   Q_OBJECT

   public:
      explicit StreamObject(QObject *parent = 0);

      double timeStep;
      double maximumTime;

      double edgeLength;
      double totalLength;

      Settings::sim::Vector vector;
      Vertex::vectorGetter getVector;

      double getEdgeLengthFactor() const;

      double getTotalLengthFactor() const;

   signals:
      void clearCache();

   public slots:
      void ontimeStepChanged(double newTimeStep);

      void onMaximumTimeChanged(double newMaximumTime);

      void onEdgeLengthFactorChanged(double newEdgeLengthFactor);

      void onMaximumTotalLengthFactorChanged(double newValue);

      void onCellSizeChanged(QSizeF currentCellSize);

   private slots:

   private:

      double edgeLengthFactor;
      double totalLengthFactor;

      double computeEdgeLength(double factor, double cellSize);

      double computeMaximumTotalLength(double factor, double cellSize);
};

#endif // STREAMOBJECT_H
