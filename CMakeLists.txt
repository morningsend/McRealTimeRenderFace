cmake_minimum_required(VERSION 2.8)
project(renderer CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

set(SOURCE_FILES src/main.cpp
        src/scene/Transform.cpp src/scene/Transform.hpp
        src/scene/Mesh.cpp src/scene/Mesh.hpp
        src/scene/Line.cpp src/scene/Line.hpp
        src/scene/Ray.cpp src/scene/Ray.hpp
        src/scene/Plane.cpp src/scene/Plane.hpp
        src/scene/Camera.cpp src/scene/Camera.hpp
        src/scene/Vertex.cpp src/scene/Vertex.hpp
        src/scene/TestModelH.h
        src/SDLauxiliary.h src/scene/Light.cpp src/scene/Light.hpp
        src/scene/Triangle.cpp src/scene/Triangle.hpp
        src/scene/Sphere.cpp src/scene/Sphere.hpp
        src/rendering/RayTracer.cpp src/rendering/RayTracer.hpp
        src/scene/Scene.cpp src/scene/Scene.hpp
        src/scene/BoundingBox.cpp src/scene/BoundingBox.hpp
        )

set(TESTS_SOURCE_FILES ${SOURCE_FILES} tests/catch.hpp src/rendering/RenderTarget.cpp src/rendering/RenderTarget.hpp src/scene/Material.cpp src/scene/Material.hpp src/scene/TextureSampler2D.cpp src/scene/TextureSampler2D.hpp src/scene/TextureMap.cpp src/scene/TextureMap.hpp tests/scene/RayTests.hpp tests/testMain.cpp src/Exception.cpp src/Exception.hpp)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories("${PROJECT_SOURCE_DIR}/lib/glm/")

find_package(sdl2 REQUIRED)

add_executable(renderer ${SOURCE_FILES})
add_executable(renderer_tests ${TESTS_SOURCE_FILES})

target_link_libraries(renderer ${SDL_LIBRARIES})
target_link_libraries(renderer_tests ${SDL_LIBRARIES})