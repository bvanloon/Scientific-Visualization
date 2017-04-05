#include "glyphsliceengine.h"
#include "settings/settings.h"
#include "settings/canvassettings.h"
#include "visualizationbuilders/translucentglyphbuilder.h"

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
   unNormalizedAlpha = Settings::sim::Scalar::fluidVelocityMagnitude;

   connectToSettings();

   emit cellSizeChanged(dynamic_cast<UniformGrid *>(visualizationGrid)->getCellSize());
}

void GlyphSliceEngine::updateCache()
{
   TranslucentGlyphBuilder builder = TranslucentGlyphBuilder(
                visualizationGrid,
                Settings::visualization::glyphs().glyph,
                Settings::visualization::glyphs().colorMap->textureGetter,
                Settings::visualization::glyphs().vectorGetter,
                Vertex::getScalarGetter(unNormalizedAlpha),
                Settings::simulation().getRange(unNormalizedAlpha));

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
   connect(&Settings::visualization::glyphs(), SIGNAL(gridDimensionChanged(QSizeF)),
           this, SLOT(onGridDimensionChanged(QSizeF)));
   connect(&Settings::visualization::glyphs(), SIGNAL(clearCache()),
            this, SLOT(onClearCache()));
}

void GlyphSliceEngine::onRecomputeVertexPositions(QSize canvasSize, QSizeF cellSize)
{
   visualizationGrid->changeGridArea(canvasSize, cellSize);
   emit cellSizeChanged(dynamic_cast<UniformGrid *>(visualizationGrid)->getCellSize());
   clearCache();
}

void GlyphSliceEngine::onGridDimensionChanged(QSizeF size)
{
   visualizationGrid = JitterGrid::createVisualizationGrid(size.width(), Settings::canvas().size, simulationGrid);
   emit cellSizeChanged(dynamic_cast<UniformGrid *>(visualizationGrid)->getCellSize());
   clearCache();
}
