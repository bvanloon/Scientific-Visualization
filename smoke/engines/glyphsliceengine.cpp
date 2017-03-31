#include "glyphsliceengine.h"
#include "grid/glyphdata.h"
#include "settings/settings.h"
#include "settings/canvassettings.h"
#include "simulation/simulationstatehistory.h"

GlyphSliceEngine::GlyphSliceEngine(UniformGrid *simulationGrid) :
   AbstractSliceEngine(AbstractEngine::lightModel::phongLight,
                       Settings::engines::EnginesTypes::glyphSlices),
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

void GlyphSliceEngine::draw(Simulation *simulation)
{
   int bufferLength = this->updateBuffers(simulation);

   drawWithMode(Settings::visualization::glyphs().drawMode, bufferLength);
}

void GlyphSliceEngine::onRecomputeVertexPositions(QSize canvasSize, QSizeF cellSize)
{
   visualizationGrid->changeGridArea(canvasSize, cellSize);
   emit cellSizeChanged(dynamic_cast<UniformGrid *>(visualizationGrid)->getCellSize());
}

int GlyphSliceEngine::updateBuffers(Simulation *UNUSED(Simulation))
{
   int idx = SimulationHistory::instance().mostRecentStateIdx();
   GlyphData data = SimulationHistory::instance().getVisualizationGridAtQueueIdx(idx).getGlyphData();
   GlyphsTriangulation glyphs = factory.createGlyphs(data, Settings::visualization::glyphs().glyph);

   updateBuffer(this->vertexBuffer, glyphs.getVertices());
   updateBuffer(this->textureCoordinateBuffer, glyphs.getTextureCoordinates());
   updateBuffer(this->normalBuffer, glyphs.getNormals());

   return glyphs.numVertices();
}

void GlyphSliceEngine::onGridDimensionChanged(int width, int UNUSED(height))
{
   visualizationGrid = JitterGrid::createVisualizationGrid(width, Settings::canvas().size, simulationGrid);
   emit cellSizeChanged(dynamic_cast<UniformGrid *>(visualizationGrid)->getCellSize());
}
