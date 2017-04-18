#ifndef STREAMSURFACES_H
#define STREAMSURFACES_H

#include <QObject>
#include <QList>
#include "settings/settings.h"
#include "settings/visualization/streamobject.h"
#include "streamobjects/seedcurve.h"

class Settings::visualization::StreamSurfaces : public StreamObject
{
   Q_OBJECT

   public:
      static const StreamSurfaces& instance();

      Settings::visualization::ColorMap *colorMap;

      int resolution;

      bool showVertices;
      bool showLines;

      SeedCurve *seedCurve;

   signals:

   public slots:
      void onWindowResized(QSizeF oldSize, QSizeF newSize);

      void onClearSeedCurves();

      void onSeedCurveVertexAdded(QPointF vertexPosition);

      void onResolutionChanged(int resolution);

      void onShowStreamSurfaceLinesToggled(bool toggle);

      void onShowStreamSurfaceVerticesToggled(bool toggle);

   private slots:

   private:
      explicit StreamSurfaces(QObject *parent = 0);
      StreamSurfaces(StreamSurfaces const&) = delete;
      void operator=(StreamSurfaces const&) = delete;

      void connectToOtherSettings();

      void transformSeedCurves(QMatrix4x4 transform);
};

#endif // STREAMSURFACES_H
