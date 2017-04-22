#include "streaksurfaceengine.h"
#include "visualizationbuilders/streaklinebuilder.h"

StreakSurfaceEngine::StreakSurfaceEngine() :
   Abstract3DEngine(AbstractEngine::lightModel::phongLight,
                    Settings::engines::EnginesTypes::streakObjects)
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
   for (streamobject::Line streakLine : streakLines) data.extend(streakLine.GPUDataVertices());
   updateBuffersAndDraw(data);
}

void StreakSurfaceEngine::drawLines(QList<streamobject::Line> streakLines)
{
   GPUData data(GL_LINES);
   for (streamobject::Line streakLine : streakLines) data.extend(streakLine.GPUDataEdges());
   updateBuffersAndDraw(data);
}

void StreakSurfaceEngine::drawSurface(QList<streamobject::Line> streakLines)
{
   streamobject::Surface surface(streakLines);
   GPUData data = surface.GPUDataSurface(Settings::visualization::streakSurface().divergenceSensitivity);
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
   return zTranslationRange.length() / (Settings::visualization::streakSurface().numberOfStates + 1);
}
