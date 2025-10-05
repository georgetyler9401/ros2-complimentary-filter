#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "std_msgs/msg/float64.hpp"
#include "complementary_filter/complementary_filter.hpp"

using std::placeholders::_1

class ComplementaryFilterNode : public rclcpp::Node {
public: 
    ComplementaryFilterNode() : Node("complementary_filter")
    {    // declare the initial parameters
    this->declare_parameter("alpha", 0.98);
    this->declare_parameter("initial_pitch", 0.0);

    // get the parameter values for the filter
    double alpha = this->get_parameter("alpha").as_double();
    double initial_pitch = this->get_parameter("initial_pitch").as_double();

    // create an instance of the filter itself
    filter_ = std::make_shared<complementary_filter::ComplementaryFilter>(alpha, intial_pitch);

    imu_sub_ = this->create_subscription<sensor_msgs::msg::Imu>(
            "/imu/data", 10, std::bind(&ComplementaryFilterNode::imuCallback, this, _1));

    pitch_pub_ = this->create_publisher<std_msgs::msg::Float64>("/pitch_estimate", 10);

    RCLCPP_INFO(this->get_logger(),
            "Complementary filter node starting")
    }

    prev_time_ = this->get_clock()->now();

private:
    void imu_callback(const sensor_msgs::msg::Imu::SharedPtr msg){

        // find the change in time since last recording
        rclcpp::Time now = get_clock()->now();
        double dt = (now - prev_time_);
        prev_time_ = now;

        // get the necessary measures from the IMU msg
        double ax = msg->linear_acceleration.x;
        double az = msg->linear_acceleration.z;
        double gy = msg->angular_velocity.y;

        // update the filter with newly read imu measures
        filter_->update(ax, az, gy, dt);

        // get the message result to publish
        std_msgs::msg::float64 out;
        out = filter_->getPitch();
        pitch_pub_->publish(out);
    }

    // define the publisher and subscriber
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_
    rclcpp::Publisher<std_msgs::msg::float64>::SharedPtr pitch_pub_

    // define the timing
    rclcpp::Time prev_time_;
};

int main(int argc, char **argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ComplementaryFilterNode>();
    rclcpp::spin();
    rclcpp::shutdown();
    return 0;
}