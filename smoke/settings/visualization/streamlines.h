#ifndef STREAMLINES_H
#define STREAMLINES_H

#include <QObject>
#include "settings/settings.h"
#include "settings/visualization/streamobject.h"
#include "grid/vertex.h"
#include <QList>
#include <QSize>
#include <QMatrix4x4>

class Settings::visualization::StreamLines : public Settings::visualization::StreamObject
{
   Q_OBJECT

   public:
      static const StreamLines& instance();

      QList<QPointF> seedPoints;

      int numberOfSeedPoints();

   signals:

   public slots:

      void onClearSeedPoints();

      void onSeedPointAdded(QPointF newSeedPoint);

      void onWindowResized(QSizeF oldSize, QSizeF newSize);

      void onAddSeedPointGrid(QSize dimension);

   private slots:

   private:
      explicit StreamLines(QObject *parent = 0);
      StreamLines(StreamLines const&) = delete;
      void operator=(StreamLines const&) = delete;

      void connectToOtherSettings();

      void transformSeedPoints(QMatrix4x4 transformationMatrix);
};

#endif // STREAMLINES_H
