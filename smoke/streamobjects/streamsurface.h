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
          QList<Line> streamLines;
    };
}

#endif // STREAMSURFACE_H
