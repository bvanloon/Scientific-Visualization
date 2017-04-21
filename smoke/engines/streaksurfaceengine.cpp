#include "streaksurfaceengine.h"
#include "visualizationbuilders/streaklinebuilder.h"

StreakSurfaceEngine::StreakSurfaceEngine(SimulationGrid *grid) :
   Abstract3DEngine(AbstractEngine::lightModel::phongLight,
                    Settings::engines::EnginesTypes::streamSurfaces),
   simulation(grid)
{}

void StreakSurfaceEngine::draw()
{
   streamobject::Surface surface = streamobject::Surface::debugSurfaceWithSplit(2);
   drawSurface(surface);
   if (Settings::visualization::streakSurface().showLines) drawLines(surface);
   if (Settings::visualization::streakSurface().showVertices) drawVertices(surface);

   GPUData data = surface.GPUDataSurfaceEdges();
   updateBuffersAndDraw(data);
}

void StreakSurfaceEngine::drawVertices(streamobject::Surface surface)
{
   static bool warningShown = false;
   if (!warningShown++) qDebug() << "StreakSurfaceEngine::drawVertices: Temporarily showing the seedpoints.";

   GPUData data(GL_POINTS);
   QList<QVector3D> seedPoints = Settings::visualization::streakSurface().seedCurve->getSeedPoints(Settings::visualization::streakSurface().resolution);
   for (QVector3D seedPoint : seedPoints)
   {
      data.addElement(seedPoint, QVector3D(0.0, 0.0, 1.0), 1.0, 1.0);
   }
//   GPUData data = surface.GPUDataVertices();
   updateBuffersAndDraw(data);
}

void StreakSurfaceEngine::drawLines(streamobject::Surface surface)
{
   static bool warningShown = false;
   if (!warningShown++) qDebug() << "StreakSurfaceEngine::drawLines: Temporarily showing the streak lines.";

   GPUData data;
   QList<QVector3D> seedPoints = Settings::visualization::streakSurface().seedCurve->getSeedPoints(Settings::visualization::streakSurface().resolution);
   for (QVector3D seedPoint : seedPoints)
   {
      StreakLineBuilder builder(seedPoint, &Settings::visualization::streakSurface(), computeZStep());
      data.extend(builder.buildLine().GPUDataEdges());
   }

//   GPUData data = surface.GPUDataLines();
   updateBuffersAndDraw(data);
}

void StreakSurfaceEngine::drawSurface(streamobject::Surface surface)
{
   static bool warningShown = false;
   if (!warningShown++) qDebug() << "StreakSurfaceEngine::drawLines: Temporarily recomputing the streak lines.";

   streamobject::Surface surface = streamobject::Surface(Settings::visualization::streakSurface().seedCurve,
                                                             Settings::visualization::streakSurface().resolution);



   GPUData data = surface.GPUDataSurface();
   updateBuffersAndDraw(data);
}

QList<QVector3D> StreakSurfaceEngine::getSeedPoints()
{
   return Settings::visualization::streakSurface().seedCurve->getSeedPoints(Settings::visualization::streakSurface().resolution);
}

QList<streamobject::Line> StreakSurfaceEngine::computeStreakLines(QList<QVector3D> seedPoints)
{}

double StreakSurfaceEngine::computeZStep()
{
   return zTranslationRange.length() / (Settings::visualization::streakSurface().getNumberOfStates() + 1);
}
