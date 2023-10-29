cmake_minimum_required(VERSION 3.5)
project(village_zhang)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

# service for to add
# 自定义接口的引入
find_package(village_interfaces REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

# ---------------- ROS2 节点一定要添加的CMakeLists.txt的一些指令 ------------------ #
# 每次建立ros节点都必须要添加
# 添加要编译的cpp文件 未来可以拓展到include文件进行编译
add_executable(zhang3_node src/zhang3.cpp)


# 添加wang2_node的节点依赖于rclcpp
# service for to add
ament_target_dependencies(zhang3_node
  rclcpp
  village_interfaces
)

# 将编译好的文件放在大目录下的install下
install(TARGETS
  zhang3_node
  DESTINATION lib/${PROJECT_NAME}
)