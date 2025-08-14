cmake_minimum_required(VERSION 3.22)

find_package(spdlog REQUIRED)

add_executable(samples
  main.cpp
)

# set compile options
if(MSVC)
# TODO
elseif(APPLE)
  target_compile_options(samples
    PUBLIC
    -Wall
    -Werror
    -Wno-unused-parameter
    -Wno-unused-function
    -Wno-unused-but-set-variable
    -Wno-unused-variable

    PRIVATE
    -fno-rtti # -fno-exceptions
  )
endif()

if(MSVC)
  target_compile_definitions(samples
    PRIVATE
    "NOMINMAX" # to undefine max, min macro
  )
endif()

target_link_libraries(samples
  PRIVATE
  spoon::spoon
  spdlog::spdlog
)

if(CMAKE_GENERATOR STREQUAL "Ninja")
  set(BINARY_OUT ${CMAKE_CURRENT_BINARY_DIR})
else()
  set(BINARY_OUT ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
endif()

# copy resources
file(GLOB_RECURSE resources "${CMAKE_CURRENT_SOURCE_DIR}/res/*.*")

foreach(resource ${resources})
  file(COPY ${resource} DESTINATION ${BINARY_OUT})
endforeach(resource)