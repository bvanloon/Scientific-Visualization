#ifndef RANGE_H
#define RANGE_H

#include <QVector2D>
#include <QVector3D>
#include <QPair>

template<class T>
class Range {
   public:
      inline Range(float minimum, float maximum) :
         pair(minimum, maximum)
      {}

      inline T minimum() const { return pair.first; }

      inline T maximum() const { return pair.second; }

      inline T length() const { return pair.second - pair.first; }

      inline void setMinimum(const T& value) { pair.first = value; }

      inline void setMaximum(const T& value) { pair.second = value; }

      inline void change(const T& minimum, const T& maximum)
      {
         setMinimum(minimum);
         setMaximum(maximum);
      }

   private:
      QPair<T, T> pair;
};

void assertInUnitRange(float t);

void assertInUnitRange(QVector2D t);

void assertInUnitRange(QVector3D t);

template<typename T>
T mapToRange(const T& input, const T& input_start, const T& input_end, const T& output_start, const T& output_end)
{
   float slope = (output_end - output_start) / static_cast<float>((input_end - input_start));

   return output_start + slope * (input - input_start);
}

template<typename T>
T mapToUnitRange(const T& input, const T& input_start, const T& input_end)
{
   float slope = 1.0 / static_cast<float>((input_end - input_start));

   return slope * (input - input_start);
}

template<typename T>
T mapToUnitRange(const T& input, const Range<T>& range)
{
   float slope = 1.0 / static_cast<float>((range.length()));

   return slope * (input - range.minimum());
}

#endif // RANGE_H
