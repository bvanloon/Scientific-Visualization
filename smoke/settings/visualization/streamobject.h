#ifndef STREAMOBJECT_H
#define STREAMOBJECT_H

#include <QObject>
#include <QSizeF>

class StreamObject : public QObject {
   Q_OBJECT

   public:
      explicit StreamObject(QObject *parent = 0);

      double timeStep;
      double maximumTime;

      double edgeLength;

      double getEdgeLengthFactor() const;

   signals:
      void clearCache();

   public slots:
      void ontimeStepChanged(double newTimeStep);

      void onMaximumTimeChanged(double newMaximumTime);

      void onEdgeLengthFactorChanged(double newEdgeLengthFactor);

      void onCellSizeChanged(QSizeF currentCellSize);

   private slots:

   private:

      double edgeLengthFactor;
      double computeEdgeLength(double factor, double cellSize);
};

#endif // STREAMOBJECT_H
