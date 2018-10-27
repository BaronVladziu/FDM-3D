cmake_minimum_required(VERSION 3.10.2)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

project(vulkan-fdm)

# STB
set(STB_DIR ${PROJECT_SOURCE_DIR}/../submodules/stb)
include_directories(${STB_DIR})

# GLFW
find_package(GLFW REQUIRED)
if (GLFW_FOUND)
    message(STATUS "Glfw found")
    include_directories(${GLFW_INCLUDE_DIRS})
    link_libraries (${GLFW_LIBRARIES})
endif (GLFW_FOUND)

# VULKAN
set(VULKAN_DIR ${PROJECT_SOURCE_DIR}/../vulkan/x86_64)
include_directories(${VULKAN_DIR}/include)
link_libraries (${VULKAN_DIR}/lib/libvulkan.so)

add_executable(${PROJECT_NAME} main.cpp App.cpp App.h Renderer.h Renderer.cpp header.h RenderVertex.cpp RenderVertex.h RenderTriangle.cpp RenderTriangle.h MapLoader.cpp MapLoader.h Map.cpp Map.h Solver.cpp Solver.h TextureType.h SolverPoint.cpp SolverPoint.h ComplexFloat.cpp ComplexFloat.h SystemOfEquations.cpp SystemOfEquations.h Matrix.cpp Matrix.h Equation.cpp Equation.h EquationValue.cpp EquationValue.h MatrixSystemOfEquations.cpp MatrixSystemOfEquations.h Complex2RealType.h ScaleType.h DimensionName.h I_SystemOfEquations.h MapMatrix.cpp MapMatrix.h MapValue.h)
