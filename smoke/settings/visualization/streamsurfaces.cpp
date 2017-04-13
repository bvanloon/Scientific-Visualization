#include "streamsurfaces.h"
#include "settings/visualizationsettings.h"
#include "settings/canvassettings.h"

Settings::visualization::StreamSurfaces::StreamSurfaces(QObject *parent) :
   QObject(parent),
   colorMap(new ColorMap()),
   resolution(3),
   showVertices(true),
   showLines(true),
   seedCurve(new SeedCurve())
{
   connectToOtherSettings();

   seedCurve->addVertex(QVector3D(20, 40, 0));
   seedCurve->addVertex(QVector3D(300, 40, 0));
   seedCurve->addVertex(QVector3D(400, 300, 0));
}

void Settings::visualization::StreamSurfaces::connectToOtherSettings()
{
   connect(&Settings::canvas(), SIGNAL(windowResized(QSizeF,QSizeF)),
           this, SLOT(onWindowResized(QSizeF,QSizeF)));
}

const Settings::visualization::StreamSurfaces& Settings::visualization::StreamSurfaces::instance()
{
   static StreamSurfaces instance;
   return instance;
}

void Settings::visualization::StreamSurfaces::onWindowResized(QSizeF oldSize, QSizeF newSize)
{
   double xScale = newSize.width() / oldSize.width();
   double yScale = newSize.height() / oldSize.height();

   QMatrix4x4 transformationMatrix;
   transformationMatrix.scale(xScale, yScale, 0.0);

   transformSeedCurves(transformationMatrix);
}

void Settings::visualization::StreamSurfaces::onClearSeedCurves()
{
   delete seedCurve;
   seedCurve = new SeedCurve();
}

void Settings::visualization::StreamSurfaces::onSeedCurveVertexAdded(QPointF vertexPosition)
{
   seedCurve->addVertex(QVector3D(Settings::canvas().convertToNormalCoordinates(vertexPosition)));
}

void Settings::visualization::StreamSurfaces::onResolutionChanged(int resolution)
{
   this->resolution = resolution;
}

void Settings::visualization::StreamSurfaces::onShowStreamSurfaceLinesToggled(bool toggle)
{
   this->showLines = toggle;
}

void Settings::visualization::StreamSurfaces::onShowStreamSurfaceVerticesToggled(bool toggle)
{
   this->showVertices = toggle;
}

void Settings::visualization::StreamSurfaces::transformSeedCurves(QMatrix4x4 transform)
{
   this->seedCurve->applyTransformation(transform);
}
