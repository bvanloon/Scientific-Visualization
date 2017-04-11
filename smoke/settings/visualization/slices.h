#ifndef SLICES_H
#define SLICES_H

#include <QObject>
#include <QStringList>

#include "settings/settings.h"

namespace Settings {
    class visualization::Slices : public QObject
    {
       Q_OBJECT

       public:
          static const Slices& instance();

          double globalAlpha;
          int numSlices;
          int numStatesPerSlice;

          enum CombinationMethods
          {
             mean,
             skip
          };

          QStringList getCombinationMethodNames() const;

       signals:
          void numberOfSlicesChanged(int newNumberOfSlices);

          void historySizeChanged(int newHistorySize);

          void numberOfStatesPerSliceChanged(int newNumberOfStates);

          void globalALphaChanged(double newGlobalAlpha);

          void clearCache();

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

    namespace defaults {
        namespace visualization {
            namespace slices {
                static const Settings::visualization::Slices::CombinationMethods combinationMethod =
                   Settings::visualization::Slices::CombinationMethods::skip;
            }
        }
    }
}

#endif // SLICES_H
