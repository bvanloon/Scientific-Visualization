#include "glyphsliceengine.h"
#include "settings/settings.h"
#include "settings/canvassettings.h"
#include "visualizationbuilders/translucentglyphbuilder.h"
#include "simulation/simulationstatehistory.h"

GlyphSliceEngine::GlyphSliceEngine() :
   AbstractSliceEngine(AbstractEngine::lightModel::phongLight,
                       Settings::engines::EnginesTypes::glyphSlices)
{
   unNormalizedAlpha = Settings::sim::Scalar::fluidVelocityMagnitude;

   connectToSettings();
}

void GlyphSliceEngine::updateCache()
{
   int idx = SimulationHistory::instance().mostRecentStateIdx();

   TranslucentGlyphBuilder builder(
      &SimulationHistory::instance().getVisualizationGridAtQueueIdx(idx),
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
   connect(&Settings::visualization::glyphs(), SIGNAL(clearCache()),
            this, SLOT(onClearCache()));
}
