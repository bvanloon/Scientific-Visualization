#ifndef STREAMLINES_H
#define STREAMLINES_H

#include <QObject>
#include "settings/settings.h"
#include "grid/vertex.h"

class Settings::visualization::StreamLines : public QObject
{
   Q_OBJECT
   public:
      static const StreamLines& instance();

      Settings::visualization::ColorMap *colorMap;
      double timeStep;
      double edgeLengthFactor;

   signals:

   public slots:
      void ontimeStepChanged(double newTimeStep);

      void onEdgeLengthFactorChanged(double newFactor);

      void onClearSeedPoints();

      void onSeedPointAdded(QPointF newSeedPoint);

   private slots:

   private:
      explicit StreamLines(QObject *parent = 0);
      StreamLines(StreamLines const&) = delete;
      void operator=(StreamLines const&) = delete;
};

#endif // STREAMLINES_H
