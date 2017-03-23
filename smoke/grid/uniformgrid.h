#ifndef UNIFORMGRID_H
#define UNIFORMGRID_H

#include "grid/grid.h"
#include <QSizeF>
#include "simulation/simulationrealization.h"
#include "streamobjects/streamline.h"

class UniformGrid : public Grid
{
   public:
      QVector<QVector3D> const& getVertexPositions() const;

      Triangulation getTriangulation() const;

      virtual void changeGridArea(QSizeF newArea);

      virtual void changeGridArea(QSizeF newArea, QSizeF padding);

      static UniformGrid *createSimulationGrid(int dimension, QSizeF size, SimulationRealization *simulation);

      static UniformGrid *createVisualizationGrid(int dimension, QSizeF size, UniformGrid *simulationGrid);

      QSizeF const& getPadding() const;

      QSizeF getCellSize() const;

      int getDimension() const;

      streamobject::Line computeStreamLine(QVector3D seedPoint,
                                           Vertex::scalarGetter textureCoordinateGetter,
                                           Vertex::vectorGetter vectorGetter);

   private:
      int dimension;
      QSizeF cellSize;
      QSizeF padding;

      UniformGrid(int dimension, QSizeF areaSize, bool hasPadding);
      UniformGrid(int dimension, QSizeF areaSize, QSizeF padding);

      void recomputeVertexPositions();

      QSizeF computeCellSize(QSizeF area);

      QSizeF computeCellSize(QSizeF area, QSizeF padding);

      int to1Dindex(int x, int y) const;

      Cell *findCellContaining(QVector3D position);

      QVector3D computeVertexPosition(int i, int j);

      Vertex *getVertexAt(int x, int y) const;

      static void createVertices(UniformGrid *grid, SimulationRealization *simulation);

      static void createVertices(UniformGrid *visualizationGrid, UniformGrid *simulationGrid);

      static void createCells(UniformGrid *grid);

      QPair<int, int> findUpperLeftOfContainingCell(QVector3D position);

      class StreamLineBuilder {
         public:
            StreamLineBuilder(Grid *grid, QVector3D currentPosition,
                              Vertex::vectorGetter vectorGetter,

                              Vertex::scalarGetter textureGetter);

            streamobject::Line getStreamLine();

         private:
            Grid *grid;

            double timeStep;
            double maximumTime;

            double edgeLength;
            double maximumTotalLength;

            Vertex::vectorGetter vectorGetter;
            Vertex::scalarGetter textureGetter;

            streamobject::Line streamLine;

            void build(QVector3D seedPoint);
            bool terminate(double currentTime);
            bool isEdgeAllowed(QVector3D origin, QVector3D destination);
            void addEdge(QVector3D origin);
            QVector3D interpolate(QVector3D previous);

      };
};

#endif // UNIFORMGRID_H
