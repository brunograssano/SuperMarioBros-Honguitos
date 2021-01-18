cmake_minimum_required(VERSION 3.9.2)
project(TP_taller_de_programacion_fiuba)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")
set(CMAKE_CXX_STANDARD 14)

# Add SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# Add SDL2 library
find_package(SDL2 REQUIRED)

# Add SDL2_image library
find_package(SDL2_image REQUIRED)

# Add SDL2_ttf library
find_package(SDL2_ttf REQUIRED)

# Add SDL2_mixer library
find_package(SDL2_mixer REQUIRED)

include_directories(${PROJECT_SOURCE_DIR})

file(GLOB_RECURSE MARIO_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE MARIO_HEADERS "${CMAKE_SOURCE_DIR}/src/*.h")

set(MARIO_INCLUDE_DIRS "")
foreach (_headerFile ${MARIO_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND MARIO_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES MARIO_INCLUDE_DIRS)

add_executable (${PROJECT_NAME} ${MARIO_SOURCES})

# Add compiler errors/warnings flags
target_compile_options(${PROJECT_NAME} PRIVATE $<$<C_COMPILER_ID:MSVC>:/W4 /WX>)
target_compile_options(${PROJECT_NAME} PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic>)

target_include_directories(${PROJECT_NAME}  PRIVATE ${MARIO_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} SDL2::Main)
target_link_libraries(${PROJECT_NAME} SDL2::Image)
target_link_libraries(${PROJECT_NAME} SDL2::TTF)
target_link_libraries(${PROJECT_NAME} SDL2::Mixer)

