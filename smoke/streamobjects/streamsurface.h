#ifndef STREAMSURFACE_H
#define STREAMSURFACE_H

#include "utilities/gpudata.h"
#include "streamobjects/streamline.h"
#include <QList>


namespace streamobject {
    class Surface
    {
       public:
          Surface();

          GPUData GPUDataVertices() const;
          GPUData GPUDataLines() const;
          GPUData GPUDataSurface() const;

          static Surface debugSurfaceWithSplit();

          void addStreamLine(Line streamLine);

       private:

          QList<Line> streamLines;

          class SurfaceBuilder;
    };

    class Surface::SurfaceBuilder {
       public:
          SurfaceBuilder(QList<Line> streamLines);

          GPUData getGPUData();

       private:
          class Vertex;
          class VertexList;

          GPUData gpuData;
          QList<VertexList> streamLines;
    };

    class Surface::SurfaceBuilder::Vertex {
       public:
          Vertex(QVector3D position, Vertex *downNeighbour, double distanceTravelled);
          ~Vertex();

          void setUpNeighbour(Vertex *value);
          void setLeftNeighbour(Vertex *value);
          void setRightNeighbour(Vertex *value);

       private:
          Vertex *downNeighbour;
          Vertex *upNeighbour;
          Vertex *leftNeighbour;
          Vertex *rightNeighbour;
    };

    class Surface::SurfaceBuilder::VertexList {
       public:
          VertexList(Line streamLine);
          ~VertexList();

          Vertex *getVertexAtLevel(int level);

       private:
          QList<Vertex *> vertices;
    };
}

#endif // STREAMSURFACE_H
