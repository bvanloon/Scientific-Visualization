#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "utilities/mesh.h"

namespace shapes {
    class Rectangle
    {
       public:
          Rectangle(double width = 1, double height = 1);

          mesh::TriangleMesh *toTriangleMesh();

       private:
          double width;
          double height;
    };
}

#endif // RECTANGLE_H
