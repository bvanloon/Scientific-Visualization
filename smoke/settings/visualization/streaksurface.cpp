#include "streaksurface.h"
#include "settings/visualizationsettings.h"
#include "settings/canvassettings.h"

Settings::visualization::StreakSurface::StreakSurface(QObject *parent) :
   StreamObject(parent),
   colorMap(new ColorMap()),
   resolution(100),
   showVertices(true), showLines(true), showSurface(true),
   divergenceSensitivity(200),
   seedCurve(new SeedCurve()),
   listeningForSeedCurveVertices(false)
{
   connectToOtherSettings();

   this->timeStep = 1.0;
   this->maximumTime = 200;
   this->numberOfStates = maximumTime;

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
   if (listeningForSeedCurveVertices) seedCurve->addVertex(QVector3D(Settings::canvas().convertToNormalCoordinates(vertexPosition)));
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

void Settings::visualization::StreakSurface::onShowStreamSurfaceFaceToggled(bool toggle)
{
   this->showSurface = toggle;
}

void Settings::visualization::StreakSurface::ontimeStepChanged(double UNUSED(newTimeStep))
{
   qDebug() << "Settings::visualization::StreakSurface::ontimeStepChanged should not be used. Timestep is not changed.";
}

void Settings::visualization::StreakSurface::onMaximumTimeChanged(double UNUSED(newMaximumTime))
{
   qDebug() << "Settings::visualization::StreakSurface::onMaximumTimeChanged should not be used. Maximum time is not changed.";
}

void Settings::visualization::StreakSurface::onNumberOfStatesChanged(int newNumberOfStates)
{
   this->maximumTime = newNumberOfStates - 1;
   this->numberOfStates = static_cast<int>(this->maximumTime);
   emit numberOfStatesChanged(newNumberOfStates);
}

void Settings::visualization::StreakSurface::onDivergenceSensitivityChanged(double sensitivity)
{
   this->divergenceSensitivity = sensitivity;
}

void Settings::visualization::StreakSurface::onToggleListenForVertices(bool toggle)
{
   this->listeningForSeedCurveVertices = toggle;
}

void Settings::visualization::StreakSurface::onRemoveLastVertexFromSeedCurve()
{
   qDebug() << "Settings::visualization::StreakSurface::onRemoveLastVertexFromSeedCurve";
}

void Settings::visualization::StreakSurface::transformSeedCurves(QMatrix4x4 transform)
{
   this->seedCurve->applyTransformation(transform);
}
