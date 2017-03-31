#include "seedpointengine.h"
#include "shapes/rectangle.h"
#include "QMatrix4x4"

const double SeedPointEngine::fillScale = 7;
const double SeedPointEngine::borderScale = 10;

SeedPointEngine::SeedPointEngine() :
   AbstractEngine(AbstractEngine::lightModel::noLight,
                  Settings::engines::EnginesTypes::seedPoints)
{}

void SeedPointEngine::draw(Simulation *UNUSED(simulation))
{
   int bufferLength = this->fillBuffers();

   drawWithMode(drawMode, bufferLength);
}

int SeedPointEngine::fillBuffers()
{
   fillIntermediateBuffers();

   int numElementsInBuffer = intermediateBufferSize();

   updateBuffer(this->vertexBuffer, vertices);
   updateBuffer(this->normalBuffer, normals);
   updateBuffer(this->textureCoordinateBuffer, textureCoordinates);

   clearIntermediateBuffers();

   return numElementsInBuffer;
}

void SeedPointEngine::fillIntermediateBuffers()
{
   for(QPointF position : Settings::visualization::streamLines().seedPoints){
       addSeedPoint(position);
   }
}

void SeedPointEngine::addSeedPoint(QPointF position)
{
   addSeedPointFill(position);
   addSeedPointBorder(position);
}

void SeedPointEngine::addSeedPointBorder(QPointF position)
{
   QPair<float, float> range = Settings::simulation().getRange(Settings::visualization::streamLines().colorMap->scalar);
   shapes::Rectangle rectangle = shapes::Rectangle(borderScale, borderScale);
   mesh::TriangleMesh *mesh = rectangle.toTriangleMesh();

   QMatrix4x4 translationMatrix;
   translationMatrix.translate(position.x(), position.y(), 0.0);
   mesh->applyTransformation(translationMatrix);

   this->addMesh(mesh, range.second);

   delete mesh;
}

void SeedPointEngine::addSeedPointFill(QPointF position)
{
   QPair<float, float> range = Settings::simulation().getRange(Settings::visualization::streamLines().colorMap->scalar);
   shapes::Rectangle rectangle = shapes::Rectangle(fillScale, fillScale);
   mesh::TriangleMesh *mesh = rectangle.toTriangleMesh();

   QMatrix4x4 translationMatrix;
   translationMatrix.translate(position.x(), position.y(), 0.0);
   mesh->applyTransformation(translationMatrix);

   this->addMesh(mesh, range.first);

   delete mesh;
}

void SeedPointEngine::addMesh(mesh::TriangleMesh *mesh, float textureCoordinate)
{
   vertices.append(mesh->getVerticesAsVBO());
   normals.append(mesh->getNormalsAsVBO());
   textureCoordinates.append(QVector<float>(mesh->numVBOVertices(), textureCoordinate));
}

void SeedPointEngine::clearIntermediateBuffers()
{
   this->vertices.clear();
   this->normals.clear();
   this->textureCoordinates.clear();
}

int SeedPointEngine::intermediateBufferSize()
{
   return this->vertices.length();
}
