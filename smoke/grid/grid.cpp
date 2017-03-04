#include "grid.h"

Grid::Grid(int numberOfVertices, bool hasPadding):
    vertices(numberOfVertices),
    vertexPositions(numberOfVertices),
    hasPadding(hasPadding)
{}

Grid::~Grid()
{
    for(int i = 0; i < vertices.size(); i++){
        delete vertices[i];
    }
    for(int i = 0; i < cells.size(); i++){
        delete cells[i];
    }
}

GlyphData Grid::getGlyphData() const
{
    qDebug() << "Grid::getGlyphData(): use variable getters for float and vector.";
    GlyphData data = GlyphData(this->numVertices());
    QVector<Vertex*>::const_iterator currentVertex = vertices.begin();
    QVector3D position;
    QVector2D vector;
    float scalar;
    for(; currentVertex != vertices.end(); currentVertex++){
        position = *((*currentVertex)->getPosition());
        vector = ((*currentVertex)->getFluidVelocity());
        scalar = (*currentVertex)->getFluidDensity();
        data.addGlyph(position, vector, scalar);
    }
    return data;
}

const QVector<QVector3D> &Grid::getVertexPositions() const
{
    return this->vertexPositions;
}

const QVector<Vertex *> &Grid::getVertices() const
{
    return this->vertices;
}

const QVector<Cell *> &Grid::getCells() const
{
    return this->cells;
}

int Grid::numVertices() const
{
    return this->vertexPositions.size();
}
