#include "streamsurfaces.h"
#include "settings/visualizationsettings.h"
#include "settings/canvassettings.h"

Settings::visualization::StreamSurfaces::StreamSurfaces(QObject *parent) :
   QObject(parent),
   colorMap(new ColorMap()),
   seedCurve(new SeedCurve()),
   resolution(3)
{
   connectToOtherSettings();
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

void Settings::visualization::StreamSurfaces::onAddVertexToSeedCurve(QPointF vertexPosition)
{
   seedCurve->addVertex(QVector3D(vertexPosition));
}

void Settings::visualization::StreamSurfaces::transformSeedCurves(QMatrix4x4 transform)
{
   qDebug() << "NOT IMPLEMENTED: Settings::visualization::StreamSurfaces::transformSeedCurves";
}
