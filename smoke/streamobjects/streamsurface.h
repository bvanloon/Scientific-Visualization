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
          GPUData GPUDataSurfaceEdges() const;
          GPUData GPUDataSurface() const;

          static Surface debugSurfaceWithSplit(double offset = 0);
          static Surface debugSurfaceWithHole(double offset = 0);

          void addStreamLine(Line streamLine);

       private:

          QList<Line> streamLines;

          class SurfaceBuilder;
    };

    class Surface::SurfaceBuilder {
       public:
          SurfaceBuilder(QList<Line> streamLines, double maximumDistanceBetweenConnectedVertices = 200);
          ~SurfaceBuilder();

          GPUData getGPUData();
          GPUData getEdgeGPUData();

       private:
          class Vertex;
          class VertexList;

          GPUData gpuData;
          QList<VertexList> streamLines;

          double maximumDistanceBetweenConnectedVertices;

          int longestStreamLineLength();

          void buildStreamLines(QList<Line> lines);
          void nextConnect();
          void nextConnectLevel(int level);
          void nextConnectStreamLinesAtLevel(int level, VertexList left, VertexList right);
          void connectVertices(Vertex *left, Vertex *right);

          GPUData buildTriangles();
          bool hasLowerLeftTriangle(Vertex *vertex);
          bool hasUpperRightTriangle(Vertex *vertex);
          GPUData buildTriangle(Vertex *a, Vertex *b, Vertex *c);

          QVector3D computeTriangleNormal(Vertex *a, Vertex *b, Vertex *c);
    };

    class Surface::SurfaceBuilder::Vertex {
       public:
          Vertex(QVector3D position, Vertex *downNeighbour);
          ~Vertex();

          QVector3D position;

          void setUpNeighbour(Vertex *upNeighbour);
          void addLeftNeighbour(Vertex *value);
          void addRightNeighbour(Vertex *leftNeighbour);

          QSet<Vertex *> getLeftNeighbours() const;

          QSet<Vertex *> getRightNeighbours() const;

          Vertex *getDownNeighbour() const;

          Vertex *getUpNeighbour() const;

          double distanceTo(Vertex other);

       private:
          Vertex *downNeighbour;
          Vertex *upNeighbour;
          QSet<Vertex *> leftNeighbours;
          QSet<Vertex *> rightNeighbours;
    };

    class Surface::SurfaceBuilder::VertexList {
       public:
          typedef QList<Vertex *>::Iterator Iterator;

          VertexList(Line streamLine, int length);
          ~VertexList();


          Iterator begin();
          Iterator end();

          int length();
          Vertex *getVertexAtLevel(int level);

       private:
          QList<Vertex *> vertices;
    };
}

#endif // STREAMSURFACE_H
