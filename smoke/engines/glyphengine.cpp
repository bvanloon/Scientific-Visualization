#include "glyphengine.h"
#include "settings/settings.h"
#include "settings/canvassettings.h"
#include "visualizationbuilders/glyphbuilder.h"


GlyphEngine::GlyphEngine(UniformGrid *simulationGrid) :
   AbstractEngine(AbstractEngine::lightModel::phongLight,
                  Settings::engines::EnginesTypes::glyphs),
   visualizationGrid(
      JitterGrid::createVisualizationGrid(
         Settings::visualization::glyphs().gridDimension.width(),
         Settings::canvas().size,
         Settings::visualization::glyphs().jitterFactor,
         simulationGrid)
      ),
   simulationGrid(simulationGrid)
{
   connnectToSettings();

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

void GlyphEngine::onReplaceGrid()
{
   visualizationGrid = JitterGrid::createVisualizationGrid(Settings::visualization::glyphs().gridDimension.width(),
                                                            Settings::canvas().size,
                                                            Settings::visualization::glyphs().jitterFactor,
                                                            simulationGrid);
   emit cellSizeChanged(dynamic_cast<UniformGrid *>(visualizationGrid)->getCellSize());
}

void GlyphEngine::connnectToSettings()
{
   connect(&Settings::visualization::glyphs(), SIGNAL(replaceGrid()),
            this, SLOT(onReplaceGrid()));
}
