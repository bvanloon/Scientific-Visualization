#ifndef STREAMSURFACE_H
#define STREAMSURFACE_H

#include "utilities/gpudata.h"
#include "streamobjects/streamline.h"
#include "streamobjects/seedcurve.h"
#include <QList>
#include <QSet>


namespace streamobject {
    class Surface
    {
       public:
          Surface();
          Surface(SeedCurve seedCurve, int resolution);
          ~Surface();

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
          Vertex(QVector3D position, double textureCoordinate, double alpha, Vertex *downNeighbour);
          ~Vertex();

          QVector3D position;
          double textureCoordinate;
          double alpha;

          Vertex *getDownNeighbour() const;
          bool hasDownNeighbour() const;

          Vertex *getUpNeighbour() const;
          void setUpNeighbour(Vertex *upNeighbour);
          bool hasUpNeighbour() const;

          double distanceTo(Vertex other) const;

          Vertex *getLeftNeighbour() const;
          void setLeftNeighbour(Vertex *value);
          bool hasLeftNeighbour() const;

          Vertex *getRightNeighbour() const;
          void setRightNeighbour(Vertex *value);
          bool hasRightNeighbour() const;

       private:
          Vertex *downNeighbour;
          Vertex *upNeighbour;
          Vertex *leftNeighbour;
          Vertex *rightNeighbour;
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
