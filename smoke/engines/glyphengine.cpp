#include "glyphengine.h"
#include "grid/glyphdata.h"
#include "settings/settings.h"
#include "settings/canvassettings.h"


GlyphEngine::GlyphEngine(UniformGrid *simulationGrid) :
   AbstractEngine(AbstractEngine::lightModel::phongLight,
                  Settings::engines::EnginesTypes::glyphs),
   visualizationGrid(
      JitterGrid::createVisualizationGrid(
         Settings::defaults::visualization::glyphs::gridSize.width(),
         Settings::canvas().size,
         simulationGrid)
      ),
   simulationGrid(simulationGrid)
{
   emit cellSizeChanged(dynamic_cast<UniformGrid *>(visualizationGrid)->getCellSize());
}

void GlyphEngine::draw()
{
   int bufferLength = this->fillBuffers();

   drawWithMode(Settings::visualization::glyphs().drawMode, bufferLength);
}

void GlyphEngine::onRecomputeVertexPositions(QSize canvasSize, QSizeF cellSize)
{
   visualizationGrid->changeGridArea(canvasSize, cellSize);
   emit cellSizeChanged(dynamic_cast<UniformGrid *>(visualizationGrid)->getCellSize());
}

void GlyphEngine::onGridDimensionChanged(int width, int UNUSED(height))
{
   visualizationGrid = JitterGrid::createVisualizationGrid(width, Settings::canvas().size, simulationGrid);
   emit cellSizeChanged(dynamic_cast<UniformGrid *>(visualizationGrid)->getCellSize());
}

int GlyphEngine::fillBuffers()
{
   GlyphData data = visualizationGrid->getGlyphData();
   GlyphsTriangulation glyphs = factory.createGlyphs(data, Settings::visualization::glyphs().glyph);

   updateBuffer(this->vertexBuffer, glyphs.getVertices());
   updateBuffer(this->textureCoordinateBuffer, glyphs.getTextureCoordinates());
   updateBuffer(this->normalBuffer, glyphs.getNormals());

   return glyphs.numVertices();
}
