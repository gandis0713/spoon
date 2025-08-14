cmake_minimum_required(VERSION 3.22)

find_package(spdlog REQUIRED)

add_executable(samples
  main.cpp
)

target_link_libraries(samples
  PRIVATE
    spoon::spoon
    spdlog::spdlog
)