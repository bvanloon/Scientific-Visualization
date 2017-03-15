#ifndef RANGE_H
#define RANGE_H

#include <QVector2D>
#include <QVector3D>

void inUnitRange(float t);
void inUnitRange(QVector2D t);
void inUnitRange(QVector3D t);

template <typename T>
T mapToRange(const T& input, const T& input_start, const T& input_end, const T& output_start, const T& output_end){
    double slope = (output_end - output_start) / static_cast<double>((input_end - input_start));
    return output_start + slope * (input - input_start);
}

#endif // RANGE_H
