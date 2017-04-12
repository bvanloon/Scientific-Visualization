#ifndef STREAMSURFACES_H
#define STREAMSURFACES_H

#include <QObject>
#include <QList>
#include "settings/settings.h"
#include "shapes/polyline.h"

class Settings::visualization::StreamSurfaces : public QObject
{
   Q_OBJECT

   public:
      static const StreamSurfaces& instance();

      Settings::visualization::ColorMap *colorMap;

      QList<shapes::PolyLine> seedCurves;

   signals:

   public slots:
      void onWindowResized(QSizeF oldSize, QSizeF newSize);

   private slots:

   private:
      explicit StreamSurfaces(QObject *parent = 0);
      StreamSurfaces(StreamSurfaces const&) = delete;
      void operator=(StreamSurfaces const&) = delete;

      void connectToOtherSettings();

      void transformSeedCurves(QMatrix4x4 transform);
};

#endif // STREAMSURFACES_H
