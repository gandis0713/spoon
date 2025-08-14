cmake_minimum_required(VERSION 3.22)

project(
  spoon
  VERSION 0.0.1
  DESCRIPTION "Implement TFLite Inference"
  LANGUAGES CXX
)

# TODO: move cmake/ directory.
if(CMAKE_SYSTEM_NAME STREQUAL "Android")
  if(CMAKE_TOOLCHAIN_FILE MATCHES "vcpkg.cmake")
    if(ANDROID_ABI MATCHES "arm64-v8a")
      set(VCPKG_TARGET_TRIPLET "arm64-android")
    elseif(ANDROID_ABI MATCHES "armeabi-v7a")
      set(VCPKG_TARGET_TRIPLET "arm-neon-android")
    elseif(ANDROID_ABI MATCHES "x86_64")
      set(VCPKG_TARGET_TRIPLET "x64-android")
    elseif(ANDROID_ABI MATCHES "x86")
      set(VCPKG_TARGET_TRIPLET "x86-android")
    endif()
  endif()
endif()

# set compile options.
set(CMAKE_CXX_STANDARD 20)

if(MSVC)
  add_compile_options(
    /MP
  )
elseif(APPLE)
  enable_language(OBJCXX)
endif()

add_subdirectory(spoon)
add_subdirectory(samples)