cmake_minimum_required(VERSION 3.8)
project(nav2_complete_coverage_helpers)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(nav2_common REQUIRED)
find_package(rclcpp REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(behaviortree_cpp_v3 REQUIRED)
find_package(nav2_util REQUIRED)

include_directories(
    include
)


set(dependencies
    rclcpp
    geometry_msgs
    nav_msgs
    behaviortree_cpp_v3
    nav2_util
)

add_library(nav2_get_start_point_bt_node SHARED src/bt_get_start_point.cpp)
list(APPEND plugin_libs nav2_get_start_point_bt_node)

foreach(bt_plugin ${plugin_libs})
    ament_target_dependencies(${bt_plugin} ${dependencies})
    target_compile_definitions(${bt_plugin} PRIVATE BT_PLUGIN_EXPORT)
endforeach()

install(TARGETS ${plugin_libs}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/
    DESTINATION include/
)

install(FILES tree_nodes.xml DESTINATION share/${PROJECT_NAME})


# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_include_directories(
    include
)

ament_export_libraries(
    ${plugin_libs}
)

ament_export_dependencies(${dependencies})

ament_package()
