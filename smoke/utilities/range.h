#ifndef RANGE_H
#define RANGE_H

#include <QVector2D>
#include <QVector3D>

void assertInUnitRange(float t);

void assertInUnitRange(QVector2D t);

void assertInUnitRange(QVector3D t);

float ensureUnitRange(float t);
QVector2D ensureUnitRange(QVector2D vector);
QVector3D ensureUnitRange(QVector3D vector);

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

#endif // RANGE_H
