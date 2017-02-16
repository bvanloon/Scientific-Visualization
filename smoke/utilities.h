#ifndef UTILS_H
#define UTILS_H


template <typename T>
T mapToRange(const T& input, const T& input_start, const T& input_end, const T& output_start, const T& output_end){
    double slope = (output_end - output_start) / static_cast<double>((input_end - input_start));
    return output_start + slope * (input - input_start);
}

#endif // UTILS_H
