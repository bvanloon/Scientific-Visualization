#ifndef STREAMLINEBUILDER_H
#define STREAMLINEBUILDER_H

#include "grid/uniformgrid.h"
#include "streamobjects/streamline.h"
#include "settings/visualization/streamobject.h"

class StreamLineBuilder {
   public:
      StreamLineBuilder(const UniformGrid *grid, QVector3D currentPosition,
                        const Settings::visualization::StreamObject *configuration);

      streamobject::Line buildLine();

   protected:
      streamobject::Line streamLine;
      const UniformGrid *grid;
      bool terminate;
      const Settings::visualization::StreamObject *configuration;

      virtual float computeMagnitude(QVector3D position);
      virtual bool isMagnitudeLargeEnough(float magnitude);

      virtual QVector3D integrate(QVector3D previousPosition);

   private:

      QVector3D seedPoint;

      void build(QVector3D seedPoint);

      bool continueBuilding(double currentTime);

      bool isEdgeAllowed(QVector3D origin, QVector3D destination);

      bool isVertexAllowed(QVector3D vertex);

      bool hasTimeLeftOver(double currentTime);

      bool isNewStreamLineLengthAllowed(QVector3D origin, QVector3D destination);

      virtual bool tryAddingVertex(QVector3D position);

      bool tryAddingEdge(QVector3D previousPosition, QVector3D position);

      bool tryAddingSeedPoint(QVector3D seedPoint);
};

#endif // STREAMLINEBUILDER_H
