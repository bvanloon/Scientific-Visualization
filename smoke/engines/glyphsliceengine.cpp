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
   connectToSettings();

   emit cellSizeChanged(dynamic_cast<UniformGrid *>(visualizationGrid)->getCellSize());
}

void GlyphSliceEngine::updateCache()
{
   GlyphBuilder builder = GlyphBuilder(visualizationGrid, Settings::visualization::glyphs().glyph,
                   Settings::visualization::glyphs().colorMap->textureGetter,
                   Settings::visualization::glyphs().vectorGetter);

   GPUData data = builder.getGPUData();
   data.transform(toSliceTransformation);

   this->cache.enqueue(data);
}

void GlyphSliceEngine::connectToSettings()
{
   connect(&Settings::simulation(), SIGNAL(recomputeVertexPositions(QSize,QSizeF)),
            this, SLOT(onRecomputeVertexPositions(QSize,QSizeF)));
   connect(this, SIGNAL(cellSizeChanged(QSizeF)),
            &Settings::visualization::glyphs(), SLOT(onCellSizeChanged(QSizeF)));
}

void GlyphSliceEngine::onRecomputeVertexPositions(QSize canvasSize, QSizeF cellSize)
{
   qDebug() << "GlyphSliceEngine::onRecomputeVertexPositions";
   visualizationGrid->changeGridArea(canvasSize, cellSize);
   emit cellSizeChanged(dynamic_cast<UniformGrid *>(visualizationGrid)->getCellSize());
}

void GlyphSliceEngine::onGridDimensionChanged(int width, int UNUSED(height))
{
   qDebug() << "GlyphSliceEngine::onGridDimensionChanged";
   visualizationGrid = JitterGrid::createVisualizationGrid(width, Settings::canvas().size, simulationGrid);
   emit cellSizeChanged(dynamic_cast<UniformGrid *>(visualizationGrid)->getCellSize());
}
