#ifndef STREAMLINES_H
#define STREAMLINES_H

#include <QObject>
#include "settings/settings.h"

class Settings::visualization::StreamLines : public QObject
{
   Q_OBJECT
   public:
      static const StreamLines& instance();

      Settings::visualization::ColorMap *ColorMap;

   signals:

   public slots:

   private slots:

   private:
      explicit StreamLines(QObject *parent = 0);
      StreamLines(StreamLines const&) = delete;
      void operator=(StreamLines const&) = delete;
};

#endif // STREAMLINES_H
