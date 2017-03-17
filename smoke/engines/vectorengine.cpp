#include "vectorengine.h"
#include "grid/glyphdata.h"
#include "settings/settings.h"
#include "settings/canvassettings.h"


VectorEngine::VectorEngine(UniformGrid *simulationGrid) :
   AbstractEngine(AbstractEngine::lightModel::phongLight),
   visualizationGrid(
      UniformGrid::createVisualizationGrid(
         Settings::defaults::visualization::glyphs::gridSize.width(),
         Settings::canvas().size,
         simulationGrid)
      ),
   simulationGrid(simulationGrid)
{
   emit cellSizeChanged(dynamic_cast<UniformGrid *>(visualizationGrid)->getCellSize());
}

void VectorEngine::draw(Simulation *simulation)
{
   int bufferLength = this->updateBuffers();

   drawWithMode(Settings::visualization::glyphs().drawMode, bufferLength);
}

void VectorEngine::onRecomputeVertexPositions(QSize canvasSize, QSizeF cellSize)
{
   visualizationGrid->changeGridArea(canvasSize, cellSize);
   emit cellSizeChanged(dynamic_cast<UniformGrid *>(visualizationGrid)->getCellSize());
}

void VectorEngine::onGridDimensionChanged(int width, int height)
{
   visualizationGrid = UniformGrid::createVisualizationGrid(width, Settings::canvas().size, simulationGrid);
   emit cellSizeChanged(dynamic_cast<UniformGrid *>(visualizationGrid)->getCellSize());
}

int VectorEngine::updateBuffers()
{
   GlyphData data = visualizationGrid->getGlyphData();
   GlyphsTriangulation glyphs = factory.createGlyphs(data, Settings::visualization::glyphs().glyph);

   updateBuffer(this->vertexBuffer, glyphs.getVertices());
   updateBuffer(this->textureCoordinateBuffer, glyphs.getTextureCoordinates());
   updateBuffer(this->normalBuffer, glyphs.getNormals());

   return glyphs.numVertices();
}
