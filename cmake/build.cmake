IF(__BUILD_INCLUDED)
  return()
ENDIF()
SET(__BUILD_INCLUDED TRUE)

# define third_party path
SET(THIRD_PARTY_DIR "${CMAKE_SOURCE_DIR}/third_party")

# define Debug and Release configurations
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Debug and Release configurations")

SET(TARGETS "" CACHE INTERNAL "Internal target list.") # This is CACHE INTERNAL
                                                       # only for its global
                                                       # status, and is always
                                                       # reset.


# global flags
IF(CMAKE_COMPILER_IS_GNUCXX)
  # Extra warnings
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wno-write-strings -Wextra")
  IF(CMAKE_CXX_FLAGS_DEBUG)
    add_definitions(-D_DEBUG)
  ELSE()
    add_definitions(-DNDEBUG)
  ENDIF()
ENDIF()

# enable file folders on generated visual studio projects
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#######  OpenGL  #######
find_package(OpenGL REQUIRED)

#######  GLUT  #######
IF(CMAKE_COMPILER_IS_GNUCXX)
  find_package(GLUT REQUIRED)
ELSE()
  SET(GLUT_ROOT_PATH "${THIRD_PARTY_DIR}/freeglut/msvc2013")
  
  SET(CMAKE_FIND_LIBRARY_PREFIXES "")
  SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib" ".dll")
  
  FIND_PATH(GLUT_INCLUDE_DIR NAMES GL/glut.h PATHS ${GLUT_ROOT_PATH}/include)
  
  FIND_LIBRARY(GLUT_LIBRARY
    NAMES freeglut glut glut32 
    PATHS ${GLUT_ROOT_PATH}/lib)

  FIND_LIBRARY(GLUT_SHARED_LIBRARY
    NAMES freeglut glut glut32 
    PATHS ${GLUT_ROOT_PATH}/bin)
ENDIF()
