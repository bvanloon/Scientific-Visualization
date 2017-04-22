#include "glyphsliceengine.h"
#include "settings/settings.h"
#include "settings/canvassettings.h"
#include "visualizationbuilders/translucentglyphbuilder.h"
#include "simulation/simulationstatehistory.h"

GlyphSliceEngine::GlyphSliceEngine() :
   AbstractSliceEngine(AbstractEngine::lightModel::phongLight,
                       Settings::engines::EnginesTypes::glyphSlices),
   unNormalizedAlpha(Settings::sim::Scalar::fluidVelocityMagnitude)
{
   connectToSettings();
}

void GlyphSliceEngine::updateCache()
{
   TranslucentGlyphBuilder builder(
      &SimulationHistory::instance().getCombinedVisualizationGridOfLastStates(
                   Settings::visualization::slices().numStatesPerSlice,
                   Settings::visualization::slices().combinationMethod),
      Settings::visualization::glyphs().glyph,
      Settings::visualization::glyphs().colorMap->textureGetter,
      Settings::visualization::glyphs().vectorGetter,
      Vertex::getScalarGetter(unNormalizedAlpha),
      Settings::simulation().getRange(unNormalizedAlpha));

   this->cache.enqueue(builder.getGPUData());
}

void GlyphSliceEngine::draw()
{
   static bool warningShown = false;
   if (!warningShown++) qDebug() << "GlyphSliceEngine::draw(): Temporary implementation of draw.";

   GPUData data = GPUData::debugCube();
   updateBuffersAndDraw(data);
}

void GlyphSliceEngine::connectToSettings()
{
   connect(&Settings::visualization::glyphs(), SIGNAL(clearCache()),
            this, SLOT(onClearCache()));
}
