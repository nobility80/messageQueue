cmake_minimum_required(VERSION 3.5)
project(ascopa)
#target_compile_features(ascopa PRIVATE cxx_std_17)
set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)


# ordered by alphabet to avoid merge conflicts
add_library(ascopa STATIC
    include/ascopa/ascopa.h
    src/ascopa/ascopa.cpp
    include/ascopa/ascoparegistry.h
    src/ascopa/ascoparegistry.cpp
)

target_include_directories(ascopa
      PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}/include
      PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/src
)


target_link_libraries(ascopa
  PRIVATE
    Threads::Threads
)

set_property(TARGET ascopa PROPERTY POSITION_INDEPENDENT_CODE ON)

# apply strict compiler warnings for internally developed code
target_compile_options(ascopa PRIVATE ${UNIT_CXX_COMPILATION_FLAGS})
target_compile_options(ascopa PUBLIC ${UNIT_CXX_COMPILATION_FLAGS})

add_subdirectory(tests)

