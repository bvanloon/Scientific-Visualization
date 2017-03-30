#ifndef SLICES_H
#define SLICES_H

#include <QObject>

#include "settings/settings.h"

class Settings::visualization::Slices : public QObject
{
   Q_OBJECT
   public:
      static const Slices& instance();

      double globalAlpha;
      double numberOfSlices;

   signals:

   public slots:

   private slots:

   private:
      explicit Slices(QObject *parent = 0);

      Slices(Slices const&) = delete;
      void operator=(Slices const&) = delete;

      void connectToOtherSettings();
};

#endif // SLICES_H
