#ifndef STREAMLINEBUILDER_H
#define STREAMLINEBUILDER_H

#include "grid/uniformgrid.h"
#include "streamobjects/streamline.h"

class StreamLineBuilder {
   public:
      StreamLineBuilder(UniformGrid *grid, QVector3D currentPosition,
                        Vertex::vectorGetter vectorGetter,
                        Vertex::scalarGetter magnitudeGetter);

      streamobject::Line getStreamLine();

   protected:
      streamobject::Line streamLine;

      float computeMagnitude(QVector3D position);
      bool isMagnitudeLargeEnoguh(float magnitude);

   private:
      UniformGrid *grid;

      double timeStep;
      double maximumTime;

      double edgeLength;
      double maximumTotalLength;

      QVector3D seedPoint;

      Vertex::vectorGetter vectorGetter;
      Vertex::scalarGetter magnitudeGetter;

      static const float minimumMagnitude;

      bool currentMagnitudeIsLargeEnough;

      void build(QVector3D seedPoint);

      bool continueBuilding(double currentTime);

      bool isEdgeAllowed(QVector3D origin, QVector3D destination);

      bool isVertexAllowed(QVector3D vertex);



      bool hasTimeLeftOver(double currentTime);

      bool isNewStreamLineLengthAllowed(QVector3D origin, QVector3D destination);

      virtual bool tryAddingVertex(QVector3D position);

      bool tryAddingEdge(QVector3D previousPosition, QVector3D position);

      bool tryAddingSeedPoint(QVector3D seedPoint);

      QVector3D integrate(QVector3D previousPosition);
};

#endif // STREAMLINEBUILDER_H
