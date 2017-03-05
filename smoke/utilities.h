#ifndef UTILS_H
#define UTILS_H

#include <QVector2D>
#include <QVector3D>

template <typename T>
T mapToRange(const T& input, const T& input_start, const T& input_end, const T& output_start, const T& output_end){
    double slope = (output_end - output_start) / static_cast<double>((input_end - input_start));
    return output_start + slope * (input - input_start);
}

float interpolateBilinearly(QVector2D position, float upperLeft, float upperRight, float lowerLeft, float lowerRight);
float interpolateBilinearly(QVector3D position, float upperLeft, float upperRight, float lowerLeft, float lowerRight);


#endif // UTILS_H
