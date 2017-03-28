#ifndef CANVASS_H
#define CANVASS_H

#include <QObject>
#include <QSize>
#include "utilities/rotation.h"

#include "settings/settings.h"

class Settings::Canvas : public QObject
{
   Q_OBJECT
   public:

      static const Canvas& instance();

      QSize size;
      Rotation rotation;

   signals:
      void windowResized(QSizeF oldSize, QSizeF newSize);
      void updateModelViewMatrix();

   public slots:
      void onWindowResized(int width, int height);
      void onRotationChanged(Rotation::axis axis, int newAngle);

   private:
      explicit Canvas(QObject *parent = 0);

      Canvas(Canvas const&) = delete;
      void operator=(Canvas const&) = delete;
};

#endif // CANVASS_H
