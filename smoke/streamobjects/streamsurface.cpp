#include "streamsurface.h"

streamobject::Surface::Surface()
{}

streamobject::Surface::Surface(SeedCurve seedCurve, int resolution)
{
   QList<QVector3D> vertices = seedCurve.getSeedPoints(resolution);
}

streamobject::Surface::~Surface()
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

GPUData streamobject::Surface::GPUDataSurfaceEdges() const
{
   GPUData data = SurfaceBuilder(this->streamLines).getEdgeGPUData();
   return data;
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
   line1.addVertex(QVector3D(100.0, 0.0 + offset, 0.0), 0.0, 0.0);
   line1.addVertex(QVector3D(100.0, 100.0, 0.0), 0.0, 0.1);
   line1.addVertex(QVector3D(55, 189, 0.0), 0.0, 0.2);
   line1.addVertex(QVector3D(10, 278, 0.0), 0.0, 0.3);
   line1.addVertex(QVector3D(0 + offset, 300, 0.0), 0.0, 0.4);
   surface.addStreamLine(line1);

   streamobject::Line line2;
   line2.addVertex(QVector3D(200, 0 + offset, 0), 3.33, 0.0);
   line2.addVertex(QVector3D(200, 100, 0), 3.33, 0.1);
   line2.addVertex(QVector3D(144, 183, 0), 3.33, 0.2);
   line2.addVertex(QVector3D(89, 266, 0), 3.33, 0.3);
   line2.addVertex(QVector3D(33, 349, 0), 3.33, 0.4);
   line2.addVertex(QVector3D(0 + offset, 400, 0), 3.33, 0.5);
   surface.addStreamLine(line2);

   streamobject::Line line3;
   line3.addVertex(QVector3D(300, 0 + offset, 0), 6.66, 0.1);
   line3.addVertex(QVector3D(300, 100, 0), 6.66, 0.2);
   line3.addVertex(QVector3D(389, 144, 0), 6.66, 0.3);
   line3.addVertex(QVector3D(478, 189, 0), 6.66, 0.4);
   line3.addVertex(QVector3D(500 - offset, 200, 0), 6.66, 0.5);
   surface.addStreamLine(line3);

   streamobject::Line line4;
   line4.addVertex(QVector3D(400, 0 + offset, 0), 10, 0.1);
   line4.addVertex(QVector3D(400, 100, 0), 10, 0.2);
   line4.addVertex(QVector3D(489, 144, 0), 10, 0.3);
   line4.addVertex(QVector3D(500 - offset, 150, 0), 10, 0.4);
   surface.addStreamLine(line4);

   return surface;
}

streamobject::Surface streamobject::Surface::debugSurfaceWithHole(double offset)
{
   double textureCoordinate = 0.0;

   streamobject::Line line1;
   QVector3D line1Vertex = QVector3D(50, offset, 0);

   streamobject::Line line2;
   QVector3D line2Vertex = QVector3D(100, offset, 0);

   streamobject::Line line9;
   QVector3D line9Vertex = QVector3D(450, offset, 0);

   streamobject::Line line10;
   QVector3D line10Vertex = QVector3D(500 - offset, offset, 0);

   for (int i = 0; i < 6; i++)
   {
      line1Vertex.setY(i * 100);
      line1.addVertex(line1Vertex, textureCoordinate);

      line2Vertex.setY(i * 100);
      line2.addVertex(line2Vertex, textureCoordinate);

      line9Vertex.setY(i * 100);
      line9.addVertex(line9Vertex, textureCoordinate);

      line10Vertex.setY(i * 100);
      line10.addVertex(line10Vertex, textureCoordinate);
   }

   streamobject::Line line3;
   line3.addVertex(QVector3D(150, 0 + offset, 0), textureCoordinate);
   line3.addVertex(QVector3D(101, 126.204, 0), textureCoordinate);
   line3.addVertex(QVector3D(111.133, 225.218, 0), textureCoordinate);
   line3.addVertex(QVector3D(125.138, 324.233, 0), textureCoordinate);
   line3.addVertex(QVector3D(139.143, 423.247, 0), textureCoordinate);
   line3.addVertex(QVector3D(150, 500 - offset, 0), textureCoordinate);

   streamobject::Line line4;
   line4.addVertex(QVector3D(200, 0 + offset, 0), textureCoordinate);
   line4.addVertex(QVector3D(155.998, 89.799, 0), textureCoordinate);
   line4.addVertex(QVector3D(111.997, 179.598, 0), textureCoordinate);
   line4.addVertex(QVector3D(138.483, 276.027, 0), textureCoordinate);
   line4.addVertex(QVector3D(164.968, 372.456, 0), textureCoordinate);
   line4.addVertex(QVector3D(191.454, 468.884, 0), textureCoordinate);
   line4.addVertex(QVector3D(200, 500 - offset, 0), textureCoordinate);

   streamobject::Line line5;
   line5.addVertex(QVector3D(250, 0 + offset, 0), textureCoordinate);
   line5.addVertex(QVector3D(190.776, 80.5764, 0), textureCoordinate);
   line5.addVertex(QVector3D(131.553, 161.153, 0), textureCoordinate);
   line5.addVertex(QVector3D(164.551, 255.552, 0), textureCoordinate);
   line5.addVertex(QVector3D(197.549, 349.951, 0), textureCoordinate);
   line5.addVertex(QVector3D(230.547, 444.349, 0), textureCoordinate);
   line5.addVertex(QVector3D(250, 500 - offset, 0), textureCoordinate);

   streamobject::Line line6;
   line6.addVertex(QVector3D(300, 0 + offset, 0), textureCoordinate);
   line6.addVertex(QVector3D(342.289, 90.6183, 0), textureCoordinate);
   line6.addVertex(QVector3D(384.577, 181.237, 0), textureCoordinate);
   line6.addVertex(QVector3D(400.866, 271.855, 0), textureCoordinate);
   line6.addVertex(QVector3D(378.267, 359.251, 0), textureCoordinate);
   line6.addVertex(QVector3D(329.668, 446.648, 0), textureCoordinate);
   line6.addVertex(QVector3D(300, 500 - offset, 0), textureCoordinate);

   streamobject::Line line7;
   line7.addVertex(QVector3D(350, 0 + offset, 0), textureCoordinate);
   line7.addVertex(QVector3D(391.791, 90.849, 0), textureCoordinate);
   line7.addVertex(QVector3D(433.581, 181.698, 0), textureCoordinate);
   line7.addVertex(QVector3D(408.184, 278.419, 0), textureCoordinate);
   line7.addVertex(QVector3D(382.786, 375.14, 0), textureCoordinate);
   line7.addVertex(QVector3D(357.389, 471.861, 0), textureCoordinate);
   line7.addVertex(QVector3D(350, 500 - offset, 0), textureCoordinate);

   streamobject::Line line8;
   line8.addVertex(QVector3D(400, 0 + offset, 0), textureCoordinate);
   line8.addVertex(QVector3D(422.877, 97.3481, 0), textureCoordinate);
   line8.addVertex(QVector3D(445.754, 194.696, 0), textureCoordinate);
   line8.addVertex(QVector3D(447.145, 294.686, 0), textureCoordinate);
   line8.addVertex(QVector3D(448.535, 394.677, 0), textureCoordinate);
   line8.addVertex(QVector3D(449.926, 494.667, 0), textureCoordinate);
   line8.addVertex(QVector3D(400, 500 - offset, 0), textureCoordinate);

   streamobject::Surface surface;
   surface.addStreamLine(line1);
   surface.addStreamLine(line2);
   surface.addStreamLine(line3);
   surface.addStreamLine(line4);
   surface.addStreamLine(line5);
   surface.addStreamLine(line6);
   surface.addStreamLine(line7);
   surface.addStreamLine(line8);
   surface.addStreamLine(line9);
   surface.addStreamLine(line10);
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
   int length = lines.first().numVertices();
   for (Line line : lines) length = qMax(length, line.numVertices());
   for (Line line : lines) this->streamLines.append(VertexList(line, length));
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
   left->setRightNeighbour(right);
   right->setLeftNeighbour(left);
}

GPUData streamobject::Surface::SurfaceBuilder::getGPUData()
{
   GPUData data(GL_TRIANGLES);
   data.extend(buildTriangles());
   return data;
}

GPUData streamobject::Surface::SurfaceBuilder::getEdgeGPUData()
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
         if (vertex->getLeftNeighbour())
         {
            this->gpuData.addElement(vertex->position, normal, textureCoordinate);
            this->gpuData.addElement(vertex->getLeftNeighbour()->position, normal, textureCoordinate);
         }
         //Edges between rightNeighbours and vertex
         if (vertex->getRightNeighbour())
         {
            this->gpuData.addElement(vertex->position, normal, textureCoordinate);
            this->gpuData.addElement(vertex->getRightNeighbour()->position, normal, textureCoordinate);
         }
      }
   }
   return this->gpuData;
}

GPUData streamobject::Surface::SurfaceBuilder::buildTriangles()
{
   GPUData data;
   for (VertexList streamLine : streamLines)
   {
      for (Vertex *vertex : streamLine)
      {
         if (hasLowerLeftTriangle(vertex)) data.extend(buildTriangle(vertex, vertex->getRightNeighbour(), vertex->getUpNeighbour()));
         if (hasUpperRightTriangle(vertex)) data.extend(buildTriangle(vertex, vertex->getLeftNeighbour(), vertex->getDownNeighbour()));
      }
   }
   return data;
}

GPUData streamobject::Surface::SurfaceBuilder::buildTriangle(Vertex *a, Vertex *b, Vertex *c)
{
   QVector3D normal = computeTriangleNormal(a, b, c);

   GPUData triangle;
   triangle.addElement(a->position, normal, a->textureCoordinate, a->alpha);
   triangle.addElement(b->position, normal, b->textureCoordinate, b->alpha);
   triangle.addElement(c->position, normal, c->textureCoordinate, c->alpha);
   return triangle;
}

QVector3D streamobject::Surface::SurfaceBuilder::computeTriangleNormal(streamobject::Surface::SurfaceBuilder::Vertex *a, streamobject::Surface::SurfaceBuilder::Vertex *b, streamobject::Surface::SurfaceBuilder::Vertex *c)
{
   QVector3D ab = b->position - a->position;
   QVector3D ac = c->position - a->position;

   return QVector3D::crossProduct(ac, ab).normalized();
}

bool streamobject::Surface::SurfaceBuilder::hasLowerLeftTriangle(streamobject::Surface::SurfaceBuilder::Vertex *vertex)
{
   if (!(vertex->hasUpNeighbour() && vertex->hasRightNeighbour())) return false;

   Vertex *rightNeighbour = vertex->getRightNeighbour();
   Vertex *upNeighbour = vertex->getUpNeighbour();
   if (!(rightNeighbour->hasUpNeighbour() && upNeighbour->hasRightNeighbour())) return false;

   return(upNeighbour->getRightNeighbour() == rightNeighbour->getUpNeighbour());
}

bool streamobject::Surface::SurfaceBuilder::hasUpperRightTriangle(streamobject::Surface::SurfaceBuilder::Vertex *vertex)
{
   if (!(vertex->hasDownNeighbour() && vertex->hasLeftNeighbour())) return false;

   Vertex *leftNeighbour = vertex->getLeftNeighbour();
   Vertex *downNeighbour = vertex->getDownNeighbour();
   if (!(leftNeighbour->hasDownNeighbour() && downNeighbour->hasLeftNeighbour())) return false;

   return(downNeighbour->getLeftNeighbour() == leftNeighbour->getDownNeighbour());
}

streamobject::Surface::SurfaceBuilder::~SurfaceBuilder()
{}

int streamobject::Surface::SurfaceBuilder::longestStreamLineLength()
{
   int maxLength = this->streamLines.first().length();
   for (VertexList streamLine : streamLines) maxLength = qMax(maxLength, streamLine.length());
   return maxLength;
}

streamobject::Surface::SurfaceBuilder::Vertex::Vertex(QVector3D position, double textureCoordinate, double alpha, streamobject::Surface::SurfaceBuilder::Vertex *downNeighbour) :
   position(position),
   textureCoordinate(textureCoordinate),
   alpha(alpha),
   downNeighbour(downNeighbour),
   upNeighbour(nullptr),
   leftNeighbour(nullptr),
   rightNeighbour(nullptr)
{}

streamobject::Surface::SurfaceBuilder::Vertex::~Vertex()
{}

void streamobject::Surface::SurfaceBuilder::Vertex::setUpNeighbour(Vertex *upNeighbour)
{
   this->upNeighbour = upNeighbour;
}

bool streamobject::Surface::SurfaceBuilder::Vertex::hasUpNeighbour() const
{
   return this->upNeighbour != nullptr;
}

double streamobject::Surface::SurfaceBuilder::Vertex::distanceTo(streamobject::Surface::SurfaceBuilder::Vertex other) const
{
   return other.position.distanceToPoint(this->position);
}

streamobject::Surface::SurfaceBuilder::Vertex *streamobject::Surface::SurfaceBuilder::Vertex::getUpNeighbour() const
{
   return upNeighbour;
}

streamobject::Surface::SurfaceBuilder::Vertex *streamobject::Surface::SurfaceBuilder::Vertex::getRightNeighbour() const
{
   return rightNeighbour;
}

void streamobject::Surface::SurfaceBuilder::Vertex::setRightNeighbour(Vertex *value)
{
   rightNeighbour = value;
}

bool streamobject::Surface::SurfaceBuilder::Vertex::hasRightNeighbour() const
{
   return this->rightNeighbour != nullptr;
}

streamobject::Surface::SurfaceBuilder::Vertex *streamobject::Surface::SurfaceBuilder::Vertex::getLeftNeighbour() const
{
   return leftNeighbour;
}

void streamobject::Surface::SurfaceBuilder::Vertex::setLeftNeighbour(Vertex *value)
{
   leftNeighbour = value;
}

bool streamobject::Surface::SurfaceBuilder::Vertex::hasLeftNeighbour() const
{
   return this->leftNeighbour != nullptr;
}

streamobject::Surface::SurfaceBuilder::Vertex *streamobject::Surface::SurfaceBuilder::Vertex::getDownNeighbour() const
{
   return downNeighbour;
}

bool streamobject::Surface::SurfaceBuilder::Vertex::hasDownNeighbour() const
{
   return this->downNeighbour != nullptr;
}

streamobject::Surface::SurfaceBuilder::VertexList::VertexList(streamobject::Line streamLine, int length)
{
   Vertex *currentVertex,
          *previousVertex = nullptr;

   for (int current = 0; vertices.length() < length; )
   {
      currentVertex = new Vertex(streamLine.vertexAt(current), streamLine.getTextureAt(current), streamLine.getAlphaAt(current), previousVertex);
      this->vertices.append(currentVertex);
      previousVertex = currentVertex;
      if (current < (streamLine.numVertices() - 1)) ++current;
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
