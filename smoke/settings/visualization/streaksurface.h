#ifndef STREAMSURFACES_H
#define STREAMSURFACES_H

#include <QObject>
#include <QList>
#include "settings/settings.h"
#include "settings/visualization/streamobject.h"
#include "streamobjects/seedcurve.h"
#include "unused.h"

class Settings::visualization::StreakSurface : public Settings::visualization::StreamObject
{
   Q_OBJECT

   public:
      static const StreakSurface& instance();

      Settings::visualization::ColorMap *colorMap;

      int resolution;

      bool showVertices;
      bool showLines;
      bool showSurface;

      double divergenceSensitivity;

      SeedCurve *seedCurve;

      int numberOfStates;

   signals:
      void numberOfStatesChanged(int newNumberOfStates);

   public slots:
      void onWindowResized(QSizeF oldSize, QSizeF newSize);

      void onClearSeedCurves();

      void onSeedCurveVertexAdded(QPointF vertexPosition);

      void onResolutionChanged(int resolution);

      void onShowStreamSurfaceLinesToggled(bool toggle);

      void onShowStreamSurfaceVerticesToggled(bool toggle);

      void onShowStreamSurfaceFaceToggled(bool toggle);

      void ontimeStepChanged(double UNUSED(newTimeStep));

      void onMaximumTimeChanged(double UNUSED(newMaximumTime));

      void onNumberOfStatesChanged(int newNumberOfStates);

      void onDivergenceSensitivityChanged(double sensitivity);

   private slots:

   private:
      explicit StreakSurface(QObject *parent = 0);
      StreakSurface(StreakSurface const&) = delete;
      void operator=(StreakSurface const&) = delete;

      void connectToOtherSettings();

      void transformSeedCurves(QMatrix4x4 transform);
};

#endif // STREAMSURFACES_H
