#include "streaksurface.h"
#include "settings/visualizationsettings.h"
#include "settings/canvassettings.h"

Settings::visualization::StreakSurface::StreakSurface(QObject *parent) :
   StreamObject(parent),
   colorMap(new ColorMap()),
   resolution(3),
   showVertices(true),
   showLines(true),
   numberOfStates(10),
   seedCurve(new SeedCurve())
{
   connectToOtherSettings();

   seedCurve->addVertex(QVector3D(20, 40, 0));
   seedCurve->addVertex(QVector3D(300, 40, 0));
   seedCurve->addVertex(QVector3D(400, 300, 0));
}

void Settings::visualization::StreakSurface::connectToOtherSettings()
{
   connect(&Settings::canvas(), SIGNAL(windowResized(QSizeF,QSizeF)),
           this, SLOT(onWindowResized(QSizeF,QSizeF)));
}

const Settings::visualization::StreakSurface& Settings::visualization::StreakSurface::instance()
{
   static StreakSurface instance;
   return instance;
}

void Settings::visualization::StreakSurface::onWindowResized(QSizeF oldSize, QSizeF newSize)
{
   double xScale = newSize.width() / oldSize.width();
   double yScale = newSize.height() / oldSize.height();

   QMatrix4x4 transformationMatrix;
   transformationMatrix.scale(xScale, yScale, 0.0);

   transformSeedCurves(transformationMatrix);
}

void Settings::visualization::StreakSurface::onClearSeedCurves()
{
   delete seedCurve;
   seedCurve = new SeedCurve();
}

void Settings::visualization::StreakSurface::onSeedCurveVertexAdded(QPointF vertexPosition)
{
   seedCurve->addVertex(QVector3D(Settings::canvas().convertToNormalCoordinates(vertexPosition)));
}

void Settings::visualization::StreakSurface::onResolutionChanged(int resolution)
{
   this->resolution = resolution;
}

void Settings::visualization::StreakSurface::onShowStreamSurfaceLinesToggled(bool toggle)
{
   this->showLines = toggle;
}

void Settings::visualization::StreakSurface::onShowStreamSurfaceVerticesToggled(bool toggle)
{
   this->showVertices = toggle;
}

void Settings::visualization::StreakSurface::onNumberOfStatesChanged(int newNumberOfStates)
{
   this->numberOfStates = newNumberOfStates;
   emit numberOfStatesChanged(newNumberOfStates);
}

void Settings::visualization::StreakSurface::transformSeedCurves(QMatrix4x4 transform)
{
   this->seedCurve->applyTransformation(transform);
}
