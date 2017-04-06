#include "slices.h"

Settings::visualization::Slices::Slices(QObject *parent) :
   QObject(parent),
   globalAlpha(1.0),
   numberOfSlices(10),
   numberOfStatesToCombineIntoASlice(10)
{
   connectToOtherSettings();
   updateHistorySize(numberOfSlices, numberOfStatesToCombineIntoASlice);
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

void Settings::visualization::Slices::onFinishedSettingUpConnections()
{
   updateHistorySize(numberOfSlices, numberOfStatesToCombineIntoASlice);
}

void Settings::visualization::Slices::onGlobalAlphaChanged(double newGlobalAlpha)
{
   this->globalAlpha = newGlobalAlpha;
   emit globalALphaChanged(newGlobalAlpha);
}

void Settings::visualization::Slices::onNumberOfSlicesChanged(int newNumberOfSlices)
{
   this->numberOfSlices = newNumberOfSlices;
   emit numberOfSlicesChanged(newNumberOfSlices);
   updateHistorySize(newNumberOfSlices, this->numberOfStatesToCombineIntoASlice);
}

void Settings::visualization::Slices::onNumberOfStatesToCombine(int newNumberOfStates)
{
   this->numberOfStatesToCombineIntoASlice = newNumberOfStates;
   emit numberOfStatesToCombineIntoASliceChanged(newNumberOfStates);
   updateHistorySize(this->numberOfSlices, newNumberOfStates);
}
