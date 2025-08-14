cmake_minimum_required(VERSION 3.22)

set(SPOON_SRC_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/model.cpp
)

add_library(spoon
  SHARED
  ${SPOON_SRC_FILES}
)
add_library(spoon::spoon ALIAS spoon)

# Set target properties
target_include_directories(spoon
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS spoon
  EXPORT spoon_targets
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)

install(EXPORT spoon_targets
  FILE spoon-config.cmake
  NAMESPACE spoon::
  DESTINATION ${CMAKE_INSTALL_PREFIX}/share/spoon
)
