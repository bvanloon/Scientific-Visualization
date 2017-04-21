#ifndef STREAKLINEBUILDER_H
#define STREAKLINEBUILDER_H

#include "visualizationbuilders/streamlinebuilder.h"
#include "settings/visualization/streamobject.h"
#include "unused.h"

class StreakLineBuilder : public StreamLineBuilder
{
   public:
      StreakLineBuilder(QVector3D currentPosition, const
                        Settings::visualization::StreamObject *configuration);

   protected:
      QVector3D integrate(QVector3D previousPosition);

      bool isMagnitudeLargeEnough(float UNUSED(magnitude));

   private:
      int currentStateIdx;

      void moveToNextGrid();
};

#endif // STREAKLINEBUILDER_H
