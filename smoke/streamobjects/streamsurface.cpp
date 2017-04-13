#include "streamsurface.h"

streamobject::Surface::Surface()
{}

GPUData streamobject::Surface::GPUDataVertices() const
{
   float textureCoordinate = 0.0;
   GPUData vertices;
   for (auto streamline : streamLines) vertices.extend(streamline.GPUDataVertices(textureCoordinate));
   return vertices;
}

GPUData streamobject::Surface::GPUDataLines() const
{
   float textureCoordinate = 0.0;
   GPUData lines;
   for (auto streamLine : streamLines) lines.extend(streamLine.GPUDataEdges(textureCoordinate));
   return lines;
}

GPUData streamobject::Surface::GPUDataSurface() const
{
   GPUData data = SurfaceBuilder(this->streamLines).getGPUData();
   return data;
}

streamobject::Surface streamobject::Surface::debugSurfaceWithSplit(double offset)
{
   streamobject::Surface surface;
   streamobject::Line line1;
   line1.addVertex(QVector3D(100.0, 0.0 + offset, 0.0), 0.0);
   line1.addVertex(QVector3D(100.0, 100.0, 0.0), 0.0);
   line1.addVertex(QVector3D(55, 189, 0.0), 0.0);
   line1.addVertex(QVector3D(10, 278, 0.0), 0.0);
   line1.addVertex(QVector3D(0 + offset, 300, 0.0), 0.0);
   surface.addStreamLine(line1);

   streamobject::Line line2;
   line2.addVertex(QVector3D(200, 0 + offset, 0), 3.33);
   line2.addVertex(QVector3D(200, 100, 0), 3.33);
   line2.addVertex(QVector3D(144, 183, 0), 3.33);
   line2.addVertex(QVector3D(89, 266, 0), 3.33);
   line2.addVertex(QVector3D(33, 349, 0), 3.33);
   line2.addVertex(QVector3D(0 + offset, 400, 0), 3.33);
   surface.addStreamLine(line2);

   streamobject::Line line3;
   line3.addVertex(QVector3D(300, 0 + offset, 0), 6.66);
   line3.addVertex(QVector3D(300, 100, 0), 6.66);
   line3.addVertex(QVector3D(389, 144, 0), 6.66);
   line3.addVertex(QVector3D(478, 189, 0), 6.66);
   line3.addVertex(QVector3D(500 - offset, 200, 0), 6.66);
   surface.addStreamLine(line3);

   streamobject::Line line4;
   line4.addVertex(QVector3D(400, 0 + offset, 0), 10);
   line4.addVertex(QVector3D(400, 100, 0), 10);
   line4.addVertex(QVector3D(489, 144, 0), 10);
   line4.addVertex(QVector3D(500 - offset, 150, 0), 10);
   surface.addStreamLine(line4);

   return surface;
}

void streamobject::Surface::addStreamLine(streamobject::Line streamLine)
{
   this->streamLines.append(streamLine);
}

streamobject::Surface::SurfaceBuilder::SurfaceBuilder(QList<streamobject::Line> streamLines, double maximumDistanceBetweenConnectedVertices) :
   gpuData(GL_LINES),
   maximumDistanceBetweenConnectedVertices(maximumDistanceBetweenConnectedVertices)
{
   buildStreamLines(streamLines);
   nextConnect();
}

void streamobject::Surface::SurfaceBuilder::buildStreamLines(QList<streamobject::Line> lines)
{
   for (Line line : lines) this->streamLines.append(VertexList(line));
}

void streamobject::Surface::SurfaceBuilder::nextConnect()
{
   int numLevels = longestStreamLineLength();
   for (int level = 0; level < numLevels; ++level) nextConnectLevel(level);
}

void streamobject::Surface::SurfaceBuilder::nextConnectLevel(int level)
{
   for (QList<VertexList>::Iterator left = streamLines.begin(), right = left + 1;
        right != streamLines.end();
        ++left, ++right) nextConnectStreamLinesAtLevel(level, *left, *right);
}

void streamobject::Surface::SurfaceBuilder::nextConnectStreamLinesAtLevel(int level, streamobject::Surface::SurfaceBuilder::VertexList left, streamobject::Surface::SurfaceBuilder::VertexList right)
{
   Vertex *leftVertex = left.getVertexAtLevel(level);
   Vertex *rightVertex = right.getVertexAtLevel(level);
   double distance = leftVertex->distanceTo(*rightVertex);
   if (distance < maximumDistanceBetweenConnectedVertices) connectVertices(leftVertex, rightVertex);
}

void streamobject::Surface::SurfaceBuilder::connectVertices(streamobject::Surface::SurfaceBuilder::Vertex *left, streamobject::Surface::SurfaceBuilder::Vertex *right)
{
   left->addRightNeighbour(right);
   right->addLeftNeighbour(left);
}

streamobject::Surface::SurfaceBuilder::~SurfaceBuilder()
{}

GPUData streamobject::Surface::SurfaceBuilder::getGPUData()
{
   QVector3D normal = QVector3D(0.0, 0.0, 1.0);
   double textureCoordinate = 10.0;
   for (VertexList streamline : streamLines)
   {
      for (Vertex *vertex : streamline)
      {
         //Edge between upNeighbour and vertex
         if (vertex->getUpNeighbour())
         {
            this->gpuData.addElement(vertex->position, normal, textureCoordinate);
            this->gpuData.addElement(vertex->getUpNeighbour()->position, normal, textureCoordinate);
         }
         //Edge between downNeighbour and vertex
         if (vertex->getDownNeighbour())
         {
            this->gpuData.addElement(vertex->position, normal, textureCoordinate);
            this->gpuData.addElement(vertex->getDownNeighbour()->position, normal, textureCoordinate);
         }
         //Edges between leftNeighbours and vertex
         for (Vertex *leftNeighbour : vertex->getLeftNeighbours())
         {
            this->gpuData.addElement(vertex->position, normal, textureCoordinate);
            this->gpuData.addElement(leftNeighbour->position, normal, textureCoordinate);
         }
         //Edges between rightNeighbours and vertex
         for (Vertex *rightNeighbour : vertex->getRightNeighbours())
         {
            this->gpuData.addElement(vertex->position, normal, textureCoordinate);
            this->gpuData.addElement(rightNeighbour->position, normal, textureCoordinate);
         }
      }
   }
   return this->gpuData;
}

int streamobject::Surface::SurfaceBuilder::longestStreamLineLength()
{
   int maxLength = this->streamLines.first().length();
   for (VertexList streamLine : streamLines) maxLength = qMax(maxLength, streamLine.length());
   return maxLength;
}

streamobject::Surface::SurfaceBuilder::Vertex::Vertex(QVector3D position, streamobject::Surface::SurfaceBuilder::Vertex *downNeighbour) :
   position(position),
   downNeighbour(downNeighbour),
   upNeighbour(nullptr)
{}

streamobject::Surface::SurfaceBuilder::Vertex::~Vertex()
{
   this->leftNeighbours.clear();
   this->rightNeighbours.clear();
}

void streamobject::Surface::SurfaceBuilder::Vertex::setUpNeighbour(Vertex *upNeighbour)
{
   this->upNeighbour = upNeighbour;
}

void streamobject::Surface::SurfaceBuilder::Vertex::addLeftNeighbour(Vertex *rightNeighbour)
{
   leftNeighbours.insert(rightNeighbour);
}

void streamobject::Surface::SurfaceBuilder::Vertex::addRightNeighbour(Vertex *leftNeighbour)
{
   rightNeighbours.insert(leftNeighbour);
}

QSet<streamobject::Surface::SurfaceBuilder::Vertex *> streamobject::Surface::SurfaceBuilder::Vertex::getRightNeighbours() const
{
   return rightNeighbours;
}

streamobject::Surface::SurfaceBuilder::Vertex *streamobject::Surface::SurfaceBuilder::Vertex::getUpNeighbour() const
{
   return upNeighbour;
}

double streamobject::Surface::SurfaceBuilder::Vertex::distanceTo(streamobject::Surface::SurfaceBuilder::Vertex other)
{
   return other.position.distanceToPoint(this->position);
}

streamobject::Surface::SurfaceBuilder::Vertex *streamobject::Surface::SurfaceBuilder::Vertex::getDownNeighbour() const
{
   return downNeighbour;
}

QSet<streamobject::Surface::SurfaceBuilder::Vertex *> streamobject::Surface::SurfaceBuilder::Vertex::getLeftNeighbours() const
{
   return leftNeighbours;
}

streamobject::Surface::SurfaceBuilder::VertexList::VertexList(streamobject::Line streamLine)
{
   Vertex *currentVertex,
          *previousVertex = nullptr;

   for (int currentIdx = 0; currentIdx < streamLine.numVertices(); ++currentIdx)
   {
      currentVertex = new Vertex(streamLine.vertexAt(currentIdx), previousVertex);
      this->vertices.append(currentVertex);
      previousVertex = currentVertex;
   }

   for (int i = 0; i < vertices.length() - 1; i++) vertices[i]->setUpNeighbour(vertices[i + 1]);
}

streamobject::Surface::SurfaceBuilder::VertexList::~VertexList()
{}

streamobject::Surface::SurfaceBuilder::VertexList::Iterator streamobject::Surface::SurfaceBuilder::VertexList::begin()
{
   return this->vertices.begin();
}

streamobject::Surface::SurfaceBuilder::VertexList::Iterator streamobject::Surface::SurfaceBuilder::VertexList::end()
{
   return this->vertices.end();
}

int streamobject::Surface::SurfaceBuilder::VertexList::length()
{
   return this->vertices.length();
}

streamobject::Surface::SurfaceBuilder::Vertex *streamobject::Surface::SurfaceBuilder::VertexList::getVertexAtLevel(int level)
{
   int actualLevel = qMin(level, this->vertices.length() - 1);
   return this->vertices[actualLevel];
}
