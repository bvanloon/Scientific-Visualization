#ifndef CANVASS_H
#define CANVASS_H

#include <QObject>
#include <QSize>
#include <QPointF>
#include <QVector3D>
#include "utilities/rotation.h"

#include "settings/settings.h"

class Settings::Canvas : public QObject
{
   Q_OBJECT
   public:

      static const Canvas& instance();

      QSize size;
      Rotation rotation;
      double scalingFactor;
      QVector3D panningPosition;

      QPointF convertToNormalCoordinates(QPointF openGLCoordinates) const;

      QVector3D convertToNormalCoordinates(QVector3D openGLCoordinates) const;

   signals:
      void windowResized(QSizeF oldSize, QSizeF newSize);

      void updateModelViewMatrix();

      void scalingFactorChanged(double newScalingFactor);

      void rotationChanged(Rotation rotation);

   public slots:
      void onWindowResized(int width, int height);

      void onRotationChanged(Rotation::axis axis, int newAngle);

      void onScalingFactorChanged(double newScalingFactor);

      void onPanningPositionChanged(QVector3D newDirection);

      void onResetView();

   private:
      explicit Canvas(QObject *parent = 0);

      double panningFactor = 10;

      Canvas(Canvas const&)         = delete;
      void operator=(Canvas const&) = delete;
};

#endif // CANVASS_H
