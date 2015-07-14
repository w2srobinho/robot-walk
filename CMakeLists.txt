if(MSVC14)
  cmake_minimum_required(VERSION 3.1)
elseif()
  cmake_minimum_required(VERSION 2.8.11)
endif()

set(CMAKE_MODULE_PATH
  "${CMAKE_MODULE_PATH}"
  "${CMAKE_SOURCE_DIR}/cmake"
)

project(animal-walk)

#includes 
include(build)

# src
add_subdirectory(app)
