#ifndef ABSTRACTGRID_H
#define ABSTRACTGRID_H

#include <QVector>
#include <QVector3D>
#include <QMultiMap>
#include <QPair>
#include "grid/glyphdata.h"
#include "grid/vertex.h"
#include "grid/cell.h"

typedef QPair<int, int> Index2D;

class Grid
{
   public:
      Grid(int numberOfVertices, bool hasPadding = true);
      virtual ~Grid();

      GlyphData getGlyphData() const;

      virtual void changeGridArea(QSizeF newArea) = 0;

      virtual void changeGridArea(QSizeF newArea, QSizeF padding) = 0;

      QVector<QVector3D> const& getVertexPositions() const;

      QVector<Vertex *> const& getVertices() const;

      QVector<Cell *> const& getCells() const;

      int numVertices() const;

      QMultiMap<Index2D, Vertex *> getVertexMap() const;

protected:
      QVector<Vertex *> vertices;
      QMultiMap<Index2D, Vertex *> vertexMap;
      QVector<QVector3D> vertexPositions;

      QVector<Cell *> cells;
      bool hasPadding;
};

#endif // ABSTRACTGRID_H
