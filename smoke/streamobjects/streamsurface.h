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

          class SurfaceBuilder;
    };

    class Surface::SurfaceBuilder {
       public:
          SurfaceBuilder(QList<Line> streamLines);

          GPUData getGPUData();

       private:
          QList<Line> streamLines;
    };
}

#endif // STREAMSURFACE_H
