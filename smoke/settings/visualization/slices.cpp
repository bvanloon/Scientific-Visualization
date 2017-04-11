#include "slices.h"

Settings::visualization::Slices::Slices(QObject *parent) :
   QObject(parent),
   globalAlpha(1.0),
   numSlices(10),
   numStatesPerSlice(10),
   combinationMethod(determineCombinationMethod(Settings::defaults::visualization::slices::combinationMethod))
{
   connectToOtherSettings();
   updateHistorySize(numSlices, numStatesPerSlice);
}

void Settings::visualization::Slices::updateHistorySize(int numberOfSlices, int numberOfStatesToCombine)
{
   int historySize = numberOfSlices * numberOfStatesToCombine;

   emit historySizeChanged(historySize);
}

SimulationHistory::SimulationGridUpdater Settings::visualization::Slices::determineCombinationMethod(Settings::visualization::Slices::CombinationMethods method)
{
   switch (method)
   {
   case CombinationMethods::skip:
      qDebug() << "Settings::visualization::Slices::determineCombinationMethod: " << "No support for the skip method.";

   case CombinationMethods::mean:
      return &SimulationHistory::updateSimulationGridToMeanOfLastStates;
   }
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
