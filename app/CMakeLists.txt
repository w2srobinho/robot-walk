cmake_minimum_required(VERSION 2.8.11)

project(app)

# Source files
set(HEADERS 
  constants.h
  mainWindow.h
  robot.h)

set(SOURCES
  main.cpp
  mainWindow.cpp)

include_directories(app ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIR} ${FREEGLUT_INCLUDE_DIR})

# Executable dependencies
add_executable(app ${HEADERS} ${SOURCES})
  
target_link_libraries(app ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${FREEGLUT_LIBRARY})

add_custom_command(TARGET app POST_BUILD            # Adds a post-build event to app
    COMMAND ${CMAKE_COMMAND} -E copy_if_different   # which executes "cmake - E copy_if_different..."
        ${GLUT_SHARED_LIBRARY}                      # <--this is in-file
        $<TARGET_FILE_DIR:app>)                     # <--this is out-file PATHS