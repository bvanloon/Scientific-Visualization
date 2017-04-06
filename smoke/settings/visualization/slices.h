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
      int numberOfSlices;
      int numberOfStatesToCombineIntoASlice;

   signals:
      void numberOfSlicesChanged(int newNumberOfSlices);

      void historySizeChanged(int newHistorySize);

      void numberOfStatesPerSliceChanged(int newNumberOfStates);

      void globalALphaChanged(double newGlobalAlpha);

   public slots:
      void onFinishedSettingUpConnections();

      void onNumberOfSlicesChanged(int newNumberOfSlices);

      void onNumberOfStatesPerSliceChanged(int newNumberOfStates);

      void onGlobalAlphaChanged(double newGlobalAlpha);

   private slots:

   private:
      explicit Slices(QObject *parent = 0);

      Slices(Slices const&) = delete;
      void operator=(Slices const&) = delete;

      void updateHistorySize(int numSlices, int numberOfStatesToCombine);

      void connectToOtherSettings();
};

#endif // SLICES_H
