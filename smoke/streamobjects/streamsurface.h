#ifndef STREAMSURFACE_H
#define STREAMSURFACE_H

#include "utilities/gpudata.h"
#include "streamobjects/streamline.h"
#include <QList>


namespace streamobject {
    class Surface
    {
       public:
          Surface();

          GPUData GPUDataVertices() const;
          GPUData GPUDataLines() const;
          GPUData GPUDataSurface() const;

       private:

          typedef QList<QPair<streamobject::Line, streamobject::Line::ConstIterator> > LineIteratorMap;

          QList<Line> streamLines;

          int numVerticesLongestStreamLine() const;

          LineIteratorMap buildLineIteratorMap() const;

          GPUData buildSurfaceLayer(LineIteratorMap& map) const;
    };
}

#endif // STREAMSURFACE_H
