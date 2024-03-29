cmake_minimum_required(VERSION 2.8)
project(renderer CXX)


set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -ffast-math")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(SOURCE_FILES
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
        src/scene/Scene.cpp src/scene/Scene.hpp
        src/scene/BoundingBox.cpp src/scene/BoundingBox.hpp
        src/rendering/FrameBuffer.cpp src/rendering/FrameBuffer.hpp src/scene/MaterialSpec.cpp src/scene/MaterialSpec.hpp tests/scene/RayTests.hpp  src/Exception.cpp src/Exception.hpp
        src/SDLauxiliary.h
        src/rendering/RasterizerConfig.hpp
        src/rendering/Renderer.cpp src/rendering/Renderer.hpp src/SDLauxiliary.cpp src/scene/Viewport.cpp src/scene/Viewport.hpp src/rendering/DeferredRenderingPipeline.cpp src/rendering/DeferredRenderingPipeline.hpp src/rendering/VertexShader.hpp src/rendering/FragmentShader.hpp src/rendering/PrimitivePreprocessor.cpp src/rendering/PrimitivePreprocessor.hpp
        src/rendering/ShaderEnvironment.hpp
        src/rendering/BasicFragmentShader.hpp
        src/textures/Texture2D.cpp src/textures/Texture2D.hpp
        src/rendering/BasicVertexShader.hpp src/rendering/Fragment.hpp
        src/rendering/VertexShader.cpp
        src/scene/TextureSampler2D.cpp src/scene/TextureSampler2D.hpp src/rendering/LightingPassFragmentShader.cpp src/rendering/LightingPassFragmentShader.hpp src/shader/Microfacet.hpp src/scene/SphericalMapSampler.cpp src/scene/SphericalMapSampler.hpp src/rendering/AntiAliasingPostProcessing.cpp src/rendering/AntiAliasingPostProcessing.hpp src/rendering/DeferredRenderingBuffers.hpp src/rendering/DeferredRenderingBuffers.cpp src/rendering/GeometryPassFragmentShader.cpp src/rendering/GeometryPassFragmentShader.hpp src/rendering/AOFragmentShader.cpp src/rendering/AOFragmentShader.hpp src/common.h)

set(TESTS_SOURCE_FILES ${SOURCE_FILES} tests/catch.hpp tests/testMain.cpp )

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(OpenCV REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/lib/glm/")


add_executable(renderer ${SOURCE_FILES} src/main.cpp)
add_executable(renderer_tests ${TESTS_SOURCE_FILES})

target_link_libraries(renderer ${SDL2_LIBRARIES} ${OpenCV_LIBS} )
target_link_libraries(renderer_tests ${SDL2_LIBRARIES} ${OpenCV_LIBS} )