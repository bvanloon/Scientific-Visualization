#ifndef STREAMSURFACES_H
#define STREAMSURFACES_H

#include <QObject>
#include "settings/settings.h"

class Settings::visualization::StreamSurfaces : public QObject
{
   Q_OBJECT

   public:
      static const StreamSurfaces& instance();

      Settings::visualization::ColorMap *colorMap;

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
