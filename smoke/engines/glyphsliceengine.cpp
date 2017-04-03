#include "glyphsliceengine.h"
#include "settings/settings.h"
#include "settings/canvassettings.h"
#include "grid/utilities/glyphbuilder.h"

GlyphSliceEngine::GlyphSliceEngine(SimulationGrid *simulationGrid) :
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

void GlyphSliceEngine::draw()
{
   GlyphBuilder builder = GlyphBuilder(visualizationGrid, Settings::visualization::glyphs().glyph,
                  Settings::visualization::glyphs().colorMap->textureGetter,
                  Settings::visualization::glyphs().vectorGetter);
   GPUData data = builder.getGPUData();
   updateBuffersAndDraw(data);
}

void GlyphSliceEngine::updateCache()
{
   std::logic_error("GlyphSliceEngine::updateCache not yet implemented");
}

void GlyphSliceEngine::onRecomputeVertexPositions(QSize canvasSize, QSizeF cellSize)
{
   visualizationGrid->changeGridArea(canvasSize, cellSize);
   emit cellSizeChanged(dynamic_cast<UniformGrid *>(visualizationGrid)->getCellSize());
}

void GlyphSliceEngine::onGridDimensionChanged(int width, int UNUSED(height))
{
   visualizationGrid = JitterGrid::createVisualizationGrid(width, Settings::canvas().size, simulationGrid);
   emit cellSizeChanged(dynamic_cast<UniformGrid *>(visualizationGrid)->getCellSize());
}
