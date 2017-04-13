#include "streamsurface.h"

streamobject::Surface::Surface()
{
   streamobject::Line line1;
   line1.addVertex(QVector3D(100.0, 0.0, 0.0), 0.0);
   line1.addVertex(QVector3D(100.0, 100.0, 0.0), 0.0);
   line1.addVertex(QVector3D(55, 189, 0.0), 0.0);
   line1.addVertex(QVector3D(10, 278, 0.0), 0.0);
   line1.addVertex(QVector3D(0, 300, 0.0), 0.0);
   this->streamLines.append(line1);

   streamobject::Line line2;
   line2.addVertex(QVector3D(200, 0, 0), 3.33);
   line2.addVertex(QVector3D(200, 100, 0), 3.33);
   line2.addVertex(QVector3D(144, 183, 0), 3.33);
   line2.addVertex(QVector3D(89, 266, 0), 3.33);
   line2.addVertex(QVector3D(33, 349, 0), 3.33);
   line2.addVertex(QVector3D(0, 400, 0), 3.33);
   this->streamLines.append(line2);

   streamobject::Line line3;
   line3.addVertex(QVector3D(300, 0, 0), 6.66);
   line3.addVertex(QVector3D(300, 100, 0), 6.66);
   line3.addVertex(QVector3D(389, 144, 0), 6.66);
   line3.addVertex(QVector3D(478, 189, 0), 6.66);
   line3.addVertex(QVector3D(500, 200, 0), 6.66);
   this->streamLines.append(line3);

   streamobject::Line line4;
   line4.addVertex(QVector3D(400, 0, 0), 10);
   line4.addVertex(QVector3D(400, 100, 0), 10);
   line4.addVertex(QVector3D(489, 144, 0), 10);
   line4.addVertex(QVector3D(500, 150, 0), 10);
   this->streamLines.append(line4);
}

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

streamobject::Surface::SurfaceBuilder::SurfaceBuilder(QList<streamobject::Line> streamLines) :
   streamLines(streamLines)
{}

GPUData streamobject::Surface::SurfaceBuilder::getGPUData()
{
   return GPUData::debugSlice();
}
