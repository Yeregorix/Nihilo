include(create_resources.cmake)
set(ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/data")
set(ASSETS_C "${CMAKE_CURRENT_BINARY_DIR}/assets.c")

create_resources(${ASSETS_DIR} ${ASSETS_C})

add_library(assets ${ASSETS_C} assets.h)
target_include_directories(assets PUBLIC .)
