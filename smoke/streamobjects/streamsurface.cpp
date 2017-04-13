#include "streamsurface.h"

streamobject::Surface::Surface()
{}

GPUData streamobject::Surface::GPUDataVertices() const
{
   float textureCoordinate = 0.0;
   GPUData vertices;
   for (auto streamline : streamLines) vertices.extend(streamline.GPUDataVertices(textureCoordinate));
   return vertices;
}

GPUData streamobject::Surface::GPUDataLines() const
{
   float textureCoordinate = 0.0;
   GPUData lines;
   for (auto streamLine : streamLines) lines.extend(streamLine.GPUDataEdges(textureCoordinate));
   return lines;
}

GPUData streamobject::Surface::GPUDataSurface() const
{
   GPUData data = SurfaceBuilder(this->streamLines).getGPUData();
   return data;
}

streamobject::Surface streamobject::Surface::debugSurfaceWithSplit()
{
   streamobject::Surface surface;
   streamobject::Line line1;
   line1.addVertex(QVector3D(100.0, 0.0, 0.0), 0.0);
   line1.addVertex(QVector3D(100.0, 100.0, 0.0), 0.0);
   line1.addVertex(QVector3D(55, 189, 0.0), 0.0);
   line1.addVertex(QVector3D(10, 278, 0.0), 0.0);
   line1.addVertex(QVector3D(0, 300, 0.0), 0.0);
   surface.addStreamLine(line1);

   streamobject::Line line2;
   line2.addVertex(QVector3D(200, 0, 0), 3.33);
   line2.addVertex(QVector3D(200, 100, 0), 3.33);
   line2.addVertex(QVector3D(144, 183, 0), 3.33);
   line2.addVertex(QVector3D(89, 266, 0), 3.33);
   line2.addVertex(QVector3D(33, 349, 0), 3.33);
   line2.addVertex(QVector3D(0, 400, 0), 3.33);
   surface.addStreamLine(line2);

   streamobject::Line line3;
   line3.addVertex(QVector3D(300, 0, 0), 6.66);
   line3.addVertex(QVector3D(300, 100, 0), 6.66);
   line3.addVertex(QVector3D(389, 144, 0), 6.66);
   line3.addVertex(QVector3D(478, 189, 0), 6.66);
   line3.addVertex(QVector3D(500, 200, 0), 6.66);
   surface.addStreamLine(line3);

   streamobject::Line line4;
   line4.addVertex(QVector3D(400, 0, 0), 10);
   line4.addVertex(QVector3D(400, 100, 0), 10);
   line4.addVertex(QVector3D(489, 144, 0), 10);
   line4.addVertex(QVector3D(500, 150, 0), 10);
   surface.addStreamLine(line4);

   return surface;
}

void streamobject::Surface::addStreamLine(streamobject::Line streamLine)
{
   this->streamLines.append(streamLine);
}

streamobject::Surface::SurfaceBuilder::SurfaceBuilder(QList<streamobject::Line> streamLines) :
   streamLines(streamLines)
{}

GPUData streamobject::Surface::SurfaceBuilder::getGPUData()
{
   return GPUData::debugSlice();
}
