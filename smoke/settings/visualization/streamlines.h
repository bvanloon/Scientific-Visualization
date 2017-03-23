#ifndef STREAMLINES_H
#define STREAMLINES_H

#include <QObject>
#include "settings/settings.h"
#include "grid/vertex.h"
#include <QList>
#include <QMatrix4x4>

class Settings::visualization::StreamLines : public QObject
{
   Q_OBJECT
   public:
      static const StreamLines& instance();

      Settings::visualization::ColorMap *colorMap;
      double timeStep;
      double maximumTime;

      double edgeLength;
      double totalLength;

      QList<QPointF> seedPoints;

      int numberOfSeedPoints();

   signals:

   public slots:
      void ontimeStepChanged(double newTimeStep);

      void onMaximumTimeChanged(double newMaximumTime);

      void onEdgeLengthFactorChanged(double newEdgeLengthFactor);

      void onMaximumTotalLengthFactorChanged(double newValue);

      void onClearSeedPoints();

      void onSeedPointAdded(QPointF newSeedPoint);

      void onWindowResized(QSizeF oldSize, QSizeF newSize);

      void onCellSizeChanged(QSizeF currentCellSize);

   private slots:

   private:
      explicit StreamLines(QObject *parent = 0);
      StreamLines(StreamLines const&) = delete;
      void operator=(StreamLines const&) = delete;

      double computeEdgeLength(double factor, double cellSize);

      double computeMaximumTotalLength(double factor, double cellSize);

      double edgeLengthFactor;
      double totalLengthFactor;

      void connectToOtherSettings();

      void transformSeedPoints(QMatrix4x4 transformationMatrix);
};

#endif // STREAMLINES_H
