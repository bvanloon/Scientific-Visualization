#include "glyphengine.h"
#include "settings/settings.h"
#include "settings/canvassettings.h"
#include "grid/utilities/glyphbuilder.h"


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
    GlyphBuilder builder = GlyphBuilder(this->visualizationGrid, Settings::visualization::glyphs().glyph,
                  Settings::visualization::glyphs().colorMap->textureGetter,
                  Settings::visualization::glyphs().vectorGetter);
    GPUData data = builder.getGPUData();
    updateBuffersAndDraw(data);
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
