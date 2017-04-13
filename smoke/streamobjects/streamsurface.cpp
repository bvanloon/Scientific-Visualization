#include "streamsurface.h"

streamobject::Surface::Surface()
{
   streamobject::Line line1;
   line1.addVertex(QVector3D(0.0, 0.0, 0.0), 0.0);
   line1.addVertex(QVector3D(50.0, 50.0, 0.0), 0.0);
   line1.addVertex(QVector3D(100.0, 100.0, 0.0), 0.0);
   line1.addVertex(QVector3D(175.0, 150.0, 0.0), 0.0);

   streamobject::Line line2;
   line2.addVertex(QVector3D(50.0, 12.5, 0.0), 5.0);
   line2.addVertex(QVector3D(100.0, 25.0, 0.0), 5.0);
   line2.addVertex(QVector3D(175.0, 150.0, 0.0), 5.0);

   streamobject::Line line3;
   line3.addVertex(QVector3D(150.0, 0, 0.0), 10.0);
   line3.addVertex(QVector3D(175.0, 37.5, 0.0), 10.0);

   this->streamLines.append(line1);
   this->streamLines.append(line2);
   this->streamLines.append(line3);
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
   QList<QPair<streamobject::Line, streamobject::Line::ConstIterator> > lineIteratorMap = buildLineIteratorMap();
   int maxNumVertices = numVerticesLongestStreamLine();
   QPair<streamobject::Line, streamobject::Line::ConstIterator> pair;
   qDebug() << "GPUData streamobject::Surface::GPUDataSurface()";
   for (int i = 0; i < maxNumVertices; i++)
   {
      for (int i = 0; i < lineIteratorMap.length(); i++)
      {
         pair = lineIteratorMap[i];
         qDebug() << *pair.second;
         if (!pair.first.isLastVertex(pair.second)) lineIteratorMap[i].second++;
      }
      qDebug() << "";
   }
   return GPUData::debugSlice();
}

QList<QPair<streamobject::Line, streamobject::Line::ConstIterator> > streamobject::Surface::buildLineIteratorMap() const
{
   QList<QPair<streamobject::Line, streamobject::Line::ConstIterator> > iterators;
   for (auto streamLine : this->streamLines)
   {
      iterators.append(QPair<streamobject::Line, streamobject::Line::ConstIterator>(streamLine, streamLine.verticesBegin()));
   }
   return iterators;
}

int streamobject::Surface::numVerticesLongestStreamLine() const
{
   int length = streamLines.first().numVertices();
   for (auto streamLine : this->streamLines) length = qMax(length, streamLine.numVertices());
   return length;
}
