#ifndef ABSTRACTTRANSLUCENTBUILDER_H
#define ABSTRACTTRANSLUCENTBUILDER_H

#include "utilities/range.h"

class AbstractTranslucentBuilder
{
   public:
      AbstractTranslucentBuilder(Range<double> range);

   protected:
      float computeAlpha(double scalar) const;

   private:
      Range<double> range;
};

#endif // ABSTRACTTRANSLUCENTBUILDER_H
