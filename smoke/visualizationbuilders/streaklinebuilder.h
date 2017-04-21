#ifndef STREAKLINEBUILDER_H
#define STREAKLINEBUILDER_H

#include "visualizationbuilders/streamlinebuilder.h"
#include "settings/visualization/streamobject.h"
#include "unused.h"

class StreakLineBuilder : public StreamLineBuilder
{
   public:
      StreakLineBuilder(QVector3D currentPosition, const
                        Settings::visualization::StreamObject *configuration,
                        double zStep);

   protected:
      QVector3D integrate(QVector3D previousPosition);

      bool isMagnitudeLargeEnough(float UNUSED(magnitude));

   private:
      int currentStateIdx;
      double zStep;

      void moveToNextGrid();
      double computeZValue(int currentStateIdx);
};

#endif // STREAKLINEBUILDER_H
