cmake_minimum_required(VERSION 3.8)
project(complementary_filter)

# Compiler warnings
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)

# Include directories
include_directories(
  include
)

# Build the complementary filter library
add_library(${PROJECT_NAME}
  src/complementary_filter.cpp
)
ament_target_dependencies(${PROJECT_NAME} rclcpp std_msgs sensor_msgs)

# Build the ROS2 node executable
add_executable(${PROJECT_NAME}_node
  src/complementary_filter_node.cpp
)
ament_target_dependencies(${PROJECT_NAME}_node rclcpp std_msgs sensor_msgs)
target_link_libraries(${PROJECT_NAME}_node ${PROJECT_NAME})

# Install targets
install(TARGETS
  ${PROJECT_NAME}
  ${PROJECT_NAME}_node
  DESTINATION lib/${PROJECT_NAME}
)

# Install header files
install(DIRECTORY include/
  DESTINATION include/
)

# Optional: testing setup
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
