#include "slices.h"

Settings::visualization::Slices::Slices(QObject *parent) :
   QObject(parent),
   globalAlpha(1.0),
   numSlices(10),
   numStatesPerSlice(10)
{
   connectToOtherSettings();
   updateHistorySize(numSlices, numStatesPerSlice);
}

void Settings::visualization::Slices::updateHistorySize(int numberOfSlices, int numberOfStatesToCombine)
{
   int historySize = numberOfSlices * numberOfStatesToCombine;

   emit historySizeChanged(historySize);
}

void Settings::visualization::Slices::connectToOtherSettings()
{}

const Settings::visualization::Slices& Settings::visualization::Slices::instance()
{
   static Slices instance;

   return instance;
}

QStringList Settings::visualization::Slices::getCombinationMethodNames() const
{
   QStringList names;

   names << "Mean"
         << "Skip";
   return names;
}

void Settings::visualization::Slices::onFinishedSettingUpConnections()
{
   updateHistorySize(numSlices, numStatesPerSlice);
}

void Settings::visualization::Slices::onGlobalAlphaChanged(double newGlobalAlpha)
{
   this->globalAlpha = newGlobalAlpha;
   emit globalALphaChanged(newGlobalAlpha);
}

void Settings::visualization::Slices::onNumberOfSlicesChanged(int newNumberOfSlices)
{
   this->numSlices = newNumberOfSlices;
   emit numberOfSlicesChanged(newNumberOfSlices);
   updateHistorySize(newNumberOfSlices, this->numStatesPerSlice);
}

void Settings::visualization::Slices::onNumberOfStatesPerSliceChanged(int newNumberOfStates)
{
   this->numStatesPerSlice = newNumberOfStates;
   emit numberOfStatesPerSliceChanged(newNumberOfStates);
   emit clearCache();
   updateHistorySize(this->numSlices, newNumberOfStates);
}
