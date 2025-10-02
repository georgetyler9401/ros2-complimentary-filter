#ifndef COMPLEMENTARY_FILTER_HPP
#define COMPLEMENTARY_FILTER_HPP

#include<cmath>

namespace complementary_filter
{
class ComplementaryFilter
{
public:
    ComplementaryFilter(double alpha, double inital_pitch = 0.0); // alpha is ration between accelerometer and gyroscope
    
    void update(double ax, double az, double gy,o, double dt); // ax, az are accelerometer readings, gy is gyroscope reading, dt is time difference

    double getPitch() const; // returns the current pitch angle

    void setAlpha(double alpha); // sets the alpha value explicitly after creation

private:
    double alpha_; // weight for accelerometer
    double pitch_; // current pitch angle
};  
} // namespace complementary_filter
#endif // COMPLEMENTARY_FILTER_HPP