#include "streamlines.h"

Settings::visualization::StreamLines::StreamLines(QObject *parent) :
   QObject(parent)
{}

const Settings::visualization::StreamLines& Settings::visualization::StreamLines::instance()
{
   static StreamLines instance;

   return instance;
}
