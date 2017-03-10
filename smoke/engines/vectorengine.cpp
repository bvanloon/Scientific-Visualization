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
      ),
   simulationGrid(simulationGrid)
{}


void VectorEngine::draw(Simulation *simulation)
{
   int bufferLength = this->updateBuffers();

   drawWithMode(GL_LINES, bufferLength);
}
void VectorEngine::onRecomputeVertexPositions(QSize canvasSize, QSizeF cellSize)
{
   visualizationGrid->changeGridArea(canvasSize, cellSize);
}
void VectorEngine::onGridDimensionChanged(int width, int height)
{
   visualizationGrid = UniformGrid::createVisualizationGrid(width, Settings::canvas().size, simulationGrid);
}
int VectorEngine::updateBuffers()
{
   GlyphsFactory::glyphs glyphType = GlyphsFactory::glyphs::hedgehog;
   GlyphData data = visualizationGrid->getGlyphData();
   GlyphsTriangulation glyphs = factory.createGlyphs(data, glyphType);
   updateBuffer(this->vertexBuffer, glyphs.getVertices());
   updateBuffer(this->textureCoordinateBuffer, glyphs.getTextureCoordinates());

   return glyphs.getVertices().length();
}
