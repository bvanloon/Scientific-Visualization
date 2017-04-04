#ifndef ABSTRACTTRANSLUCENTBUILDER_H
#define ABSTRACTTRANSLUCENTBUILDER_H

#include <QPair>

typedef QPair<float, float> Range;

class AbstractTranslucentBuilder
{
   public:
      AbstractTranslucentBuilder(Range range);

   protected:
      float computeAlpha(float scalar) const;

private:
      Range range;
};

#endif // ABSTRACTTRANSLUCENTBUILDER_H
