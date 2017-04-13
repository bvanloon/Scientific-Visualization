#ifndef STREAMSURFACE_H
#define STREAMSURFACE_H

#include "utilities/gpudata.h"
#include "streamobjects/streamline.h"
#include <QList>
#include <QSet>


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
          ~SurfaceBuilder();

          GPUData getGPUData();

       private:
          class Vertex;
          class VertexList;

          GPUData gpuData;
          QList<VertexList> streamLines;
    };

    class Surface::SurfaceBuilder::Vertex {
       public:
          Vertex(QVector3D position, Vertex *downNeighbour);
          ~Vertex();

          void setUpNeighbour(Vertex *upNeighbour);
          void addLeftNeighbour(Vertex *value);
          void addRightNeighbour(Vertex *leftNeighbour);

          QSet<Vertex *> getLeftNeighbours() const;

          QSet<Vertex *> getRightNeighbours() const;

       private:
          QVector3D position;

          Vertex *downNeighbour;
          Vertex *upNeighbour;
          QSet<Vertex *> leftNeighbours;
          QSet<Vertex *> rightNeighbours;
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
