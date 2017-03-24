#ifndef STREAMLINEBUILDER_H
#define STREAMLINEBUILDER_H

#include "grid/uniformgrid.h"
#include "streamobjects/streamline.h"

class UniformGrid::StreamLineBuilder {
   public:
      StreamLineBuilder(UniformGrid *grid, QVector3D currentPosition,
                        Vertex::vectorGetter vectorGetter,
                        Vertex::scalarGetter magnitudeGetter);

      streamobject::Line getStreamLine();

   private:
      UniformGrid *grid;

      double timeStep;
      double maximumTime;

      double edgeLength;
      double maximumTotalLength;

      Vertex::vectorGetter vectorGetter;
      Vertex::scalarGetter magnitudeGetter;

      static const float minimumMagnitude;

      bool currentMagnitudeIsNearZero;

      streamobject::Line streamLine;

      void build(QVector3D seedPoint);

      bool terminate(double currentTime);

      bool isEdgeAllowed(QVector3D origin, QVector3D destination);

      bool isVertexAllowed(QVector3D vertex);

      bool hasTimeLeftOver(double currentTime);

      bool isEdgeLengthAllowed(QVector3D origin, QVector3D destination);

      void addVertex(QVector3D position);

      bool tryAddingEdge(QVector3D previousPosition, QVector3D position);

      bool tryAddingSeedPoint(QVector3D seedPoint);

      float computeMagnitude(QVector3D position);

      QVector3D integrate(QVector3D previousPosition);
};

#endif // STREAMLINEBUILDER_H
