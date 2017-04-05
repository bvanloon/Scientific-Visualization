#include "abstracttranslucentbuilder.h"
#include "utilities/range.h"

AbstractTranslucentBuilder::AbstractTranslucentBuilder(Range<double> range) :
   range(range)
{}

float AbstractTranslucentBuilder::computeAlpha(double scalar) const
{
   return mapToUnitRange(scalar, range.minimum(), range.maximum());
}
