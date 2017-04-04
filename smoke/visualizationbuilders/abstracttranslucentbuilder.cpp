#include "abstracttranslucentbuilder.h"
#include "utilities/range.h"

AbstractTranslucentBuilder::AbstractTranslucentBuilder(Range range) :
   range(range)
{}

float AbstractTranslucentBuilder::computeAlpha(float scalar)
{
   return mapToUnitRange(scalar, range.first, range.second);
}
