#ifndef STREAKLINEBUILDER_H
#define STREAKLINEBUILDER_H

#include "visualizationbuilders/streamlinebuilder.h"
#include "settings/visualization/streamobject.h"

class StreakLineBuilder : public StreamLineBuilder
{
   public:
      StreakLineBuilder(QVector3D currentPosition, const
                        Settings::visualization::StreamObject *configuration);

   protected:
      QVector3D integrate(QVector3D previousPosition);
};

#endif // STREAKLINEBUILDER_H
