set(SOURCES 
  iterator.c
  vector.c
  stack.c)

add_library(csvl SHARED ${SOURCES})

set_target_properties(csvl PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(csvl PUBLIC ${PROJECT_SOURCE_DIR}/inc PRIVATE .)
