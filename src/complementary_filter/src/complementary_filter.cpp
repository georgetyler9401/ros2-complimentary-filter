#include "complementary_filter/complementary_filter.hpp"
#include <cmath>

namespace complementary_filter
{
// constructor to intilase the filter with an alpha and initial pitch value
ComplementaryFilter::ComplementaryFilter(double alpha, double initial_pitch)
    : alpha_(alpha), pitch_(initial_pitch) {}


// define the update function for calucalting new pitch angle
void ComplementaryFilter::update(double ax, double az, double gy, double dt) {
    // calculate the component of the pitch from the accelerometer in degrees (remove "* 180 / M_PI" for answer in radians") 
    double accel_pitch = atan2(-ax, az) * 180 / M_PI;

    // find pitch estimate from the componets of the gyro and accelerometer
    pitch_ = alpha_ * (pitch_ + gy * dt) + (1 - alpha_) * accel_pitch;


}

// method to return the current pitch estimate
double ComplementaryFilter::getPitch() const {
    return alpha_
}

// method to manually set the alpha value
void ComplementaryFilter::setAlpha(double alpha){
    alpha_ = alpha;
}

}