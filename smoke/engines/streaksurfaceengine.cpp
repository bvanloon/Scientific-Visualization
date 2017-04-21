#include "streaksurfaceengine.h"
#include "visualizationbuilders/streaklinebuilder.h"

StreakSurfaceEngine::StreakSurfaceEngine(SimulationGrid *grid) :
   Abstract3DEngine(AbstractEngine::lightModel::phongLight,
                    Settings::engines::EnginesTypes::streamSurfaces),
   simulation(grid)
{}

void StreakSurfaceEngine::draw()
{
   QList<streamobject::Line> streakLines = computeStreakLines(getSeedPoints());

   if (Settings::visualization::streakSurface().showSurface) drawSurface(streakLines);
   if (Settings::visualization::streakSurface().showLines) drawLines(streakLines);
   if (Settings::visualization::streakSurface().showVertices) drawVertices(streakLines);
}

void StreakSurfaceEngine::drawVertices(QList<streamobject::Line> streakLines)
{
   GPUData data(GL_POINTS);
   for (streamobject::Line streakLine : streakLines) data.extend(streakLine.GPUDataVertices(0.0));
   updateBuffersAndDraw(data);
}

void StreakSurfaceEngine::drawLines(streamobject::Surface surface)
{
   static bool warningShown = false;
   if (!warningShown++) qDebug() << "StreakSurfaceEngine::drawLines: Temporarily recomputing the streaklines.";

   GPUData data;

   QList<streamobject::Line> streakLines = computeStreakLines(getSeedPoints());
   for (streamobject::Line streakLine : streakLines) data.extend(streakLine.GPUDataEdges());

//   GPUData data = surface.GPUDataLines();
   updateBuffersAndDraw(data);
}

void StreakSurfaceEngine::drawSurface(streamobject::Surface surface)
{
//   static bool warningShown = false;
//   if (!warningShown++) qDebug() << "StreakSurfaceEngine::drawLines: Temporarily recomputing the streak lines.";

   streamobject::Surface theSurface(computeStreakLines(getSeedPoints()));
   GPUData data = theSurface.GPUDataSurface();
   updateBuffersAndDraw(data);
}

QList<QVector3D> StreakSurfaceEngine::getSeedPoints()
{
   return Settings::visualization::streakSurface().seedCurve->getSeedPoints(Settings::visualization::streakSurface().resolution);
}

QList<streamobject::Line> StreakSurfaceEngine::computeStreakLines(QList<QVector3D> seedPoints)
{
   QList<streamobject::Line> streamLines;
   for (QVector3D seedPoint : seedPoints)
   {
      StreakLineBuilder builder(seedPoint, &Settings::visualization::streakSurface(), computeZStep());
      streamLines.append(builder.buildLine());
   }
   return streamLines;
}

double StreakSurfaceEngine::computeZStep()
{
   return zTranslationRange.length() / (Settings::visualization::streakSurface().getNumberOfStates() + 1);
}
