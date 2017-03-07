#include "vectorengine.h"
#include "grid/glyphdata.h"
#include "settings/settings.h"
#include "settings/canvassettings.h"


VectorEngine::VectorEngine(UniformGrid *simulationGrid) :
   AbstractEngine(),
   visualizationGrid(
      UniformGrid::createVisualizationGrid(
         Settings::defaults::visualization::glyphs::gridSize.width(),
         Settings::canvas().size,
         simulationGrid)
      )
{
}


void VectorEngine::draw(Simulation *simulation)
{
   int bufferLength = this->updateBuffers(simulation);

   drawWithMode(simulation, GL_LINES, bufferLength);
}


void VectorEngine::onRecomputeVertexPositions(QSize canvasSize, QSizeF cellSize)
{
   visualizationGrid->changeGridArea(canvasSize, cellSize);
}


void VectorEngine::onGridDimensionChanged(int width, int height)
{
   qDebug() << "VectorEngine::onGridDimensionChanged: Handle the change in the dimension of the visualization grid.";
}


int VectorEngine::updateBuffers(Simulation *simulation)
{
   GlyphData data = visualizationGrid->getGlyphData();

   QVector<QVector3D> vertices;
   QVector<float> textureCoordinates;

   for (int i = 0; i < data.numGlyphs(); i++)
   {
      vertices.append(data.getPositions().at(i));
      vertices.append(data.getPositions().at(
                      i) + Settings::visualization().vectorScale *
                    data.getVectors().at(i));

      textureCoordinates.append(data.getScalars().at(i));
      textureCoordinates.append(data.getScalars().at(i));
   }

   updateBuffer(this->vertexBuffer, vertices);
   updateBuffer(this->textureCoordinateBuffer, textureCoordinates);
   return vertices.length();
}
