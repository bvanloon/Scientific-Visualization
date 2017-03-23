#ifndef CANVASS_H
#define CANVASS_H

#include <QObject>
#include <QSize>

#include "settings/settings.h"

class Settings::Canvas : public QObject
{
   Q_OBJECT
   public:

      static const Canvas& instance();

      QSize size;

   signals:
      void windowResized(QSizeF oldSize, QSizeF newSize);

   public slots:
      void onWindowResized(int width, int height);

   private:
      explicit Canvas(QObject *parent = 0);

      Canvas(Canvas const&) = delete;
      void operator=(Canvas const&) = delete;
};

#endif // CANVASS_H
