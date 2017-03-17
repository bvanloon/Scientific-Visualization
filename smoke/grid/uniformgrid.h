#ifndef UNIFORMGRID_H
#define UNIFORMGRID_H

#include "grid/grid.h"
#include <QSizeF>
#include "simulation/simulationrealization.h"
#include "streamobjects/streamline.h"
#include <QRectF>

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

      bool inGridArea(QVector3D position) const;

      streamobject::Line computeStreamLine(QVector3D seedPoint,
                                           Vertex::scalarGetter textureCoordinateGetter,
                                           Vertex::vectorGetter vectorGetter);

   protected:
      UniformGrid(int dimension, QSizeF areaSize, bool hasPadding);
      UniformGrid(int dimension, QSizeF areaSize, QSizeF padding);

      static void createVertices(UniformGrid *grid, SimulationRealization *simulation);

      static void createVertices(UniformGrid *visualizationGrid, UniformGrid *simulationGrid);


      static void createCells(UniformGrid *grid);

      virtual QVector3D computeVertexPosition(int i, int j);

      int dimension;
      QSizeF cellSize;
      QSizeF padding;

   private:
      QRectF coveredArea;
      void recomputeVertexPositions();

      QSizeF computeCellSize(QSizeF area);

      QSizeF computeCellSize(QSizeF area, QSizeF padding);

      QRectF computeCoveredArea(QSizeF padding, QSizeF cellSize);

      int to1Dindex(int x, int y) const;

      StructuredCell *findCellContaining(QVector3D position);



      Vertex *getVertexAt(int x, int y) const;

      QPair<int, int> findUpperLeftOfContainingCell(QVector3D position);

      class StreamLineBuilder {
         public:
            StreamLineBuilder(UniformGrid *grid, QVector3D currentPosition,
                              Vertex::vectorGetter vectorGetter,

                              Vertex::scalarGetter textureGetter);

            streamobject::Line getStreamLine();

         private:
            UniformGrid *grid;

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

            bool isVertexAllowed(QVector3D vertex);

            bool isEdgeLengthAllowed(QVector3D origin, QVector3D destination);

            void addVertex(QVector3D position);

            bool tryAddingEdge(QVector3D previousPosition, QVector3D position);

            bool tryAddingSeedPoint(QVector3D seedPoint);

            float computeTextureCoordiante(QVector3D position);

            QVector3D integrate(QVector3D previousPosition);
      };
};

#endif // UNIFORMGRID_H
