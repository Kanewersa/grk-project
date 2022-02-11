cmake_minimum_required(VERSION 3.10)

project("zombies")

set(APP_NAME "Zombies")
set(CMAKE_CXX_STANDARD 20)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories("libraries/glm")
include_directories("libraries/glad")
include_directories("libraries/stb")
include_directories("libraries/entt")

if (APPLE)
    find_package(assimp REQUIRED)
    find_package(GLFW3 REQUIRED)
    find_package(OpenGL REQUIRED)
    find_package(glfw3 REQUIRED)

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa -framework OpenGL -framework IOKit -framework GLUT")
    add_compile_options(-DCMAKE_APPLE_SILICON_PROCESSOR=arm64)

    set(GLFW_PATH glfw)
    set(ASSIMP_PATH assimp::assimp)
    set(IMGUI_PATH imgui::imgui)
endif (APPLE)

if (WIN32)
    include_directories("libraries/glfw/include")
    include_directories("libraries/assimp/include")
    include_directories("libraries/imgui/")
    include_directories("libraries/rocket/")

    add_library(imgui STATIC
            libraries/imgui/imgui.cpp
            libraries/imgui/imgui_draw.cpp
            libraries/imgui/imgui_demo.cpp
            libraries/imgui/imgui_tables.cpp
            libraries/imgui/imgui_widgets.cpp
            libraries/imgui/imgui_impl_glfw.cpp
            libraries/imgui/backends/imgui_impl_opengl3.cpp)

    find_package(OpenGL REQUIRED)

    set(GLFW_PATH ../libraries/glfw/lib/glfw3)
    set(ASSIMP_PATH ../libraries/assimp/lib/assimp-vc140-mt)
    set(IMGUI_PATH imgui)
endif (WIN32)

add_executable(zombies "src/main.cpp" "libraries/rocket/rocket.hpp" "libraries/glad/gl.c" "src/zombies.cpp" "src/zombies.h" "src/window.cpp" "src/window.h" "src/game.h" "src/game.cpp" "src/engine/shader.h" "src/engine/shader.cpp" src/camera.cpp src/camera.h src/engine/texture.h src/engine/texture.cpp src/engine/texture_manager.h src/engine/texture_manager.cpp src/engine/sprite_batch.h src/engine/sprite_batch.cpp src/engine/texture_render_target.h src/engine/texture_render_target.cpp src/input_manager.h src/ecs/world.cpp src/ecs/world.h src/ecs/components/transform_component.h src/ecs/components/animated_model_component.h src/ecs/systems/render_system.cpp src/ecs/systems/render_system.h src/ecs/components/player_component.h src/ecs/systems/movement_system.cpp src/ecs/systems/movement_system.h src/ecs/components/movement_component.h src/ecs/systems/camera_system.cpp src/ecs/systems/camera_system.h src/ecs/components/camera_focus_component.h src/utils.h src/engine/cubemap.cpp src/engine/cubemap.h src/engine/skybox.cpp src/engine/skybox.h src/engine/water/water_frame_buffers.h src/ecs/systems/ui_render_system.cpp src/ecs/systems/ui_render_system.h src/engine/animations/animation.cpp src/engine/animations/animation.h src/engine/animations/bone.cpp src/engine/animations/bone.h src/engine/animations/mesh.cpp src/engine/animations/mesh.h src/engine/animations/model.cpp src/engine/animations/model.h src/engine/animations/animator.cpp src/engine/animations/animator.h src/engine/timer.h src/ecs/components/model_component.h src/engine/lighting_data.h src/print.h src/ecs/systems/terrain_system.cpp src/ecs/systems/terrain_system.h src/ecs/systems/noise.h src/ecs/systems/test_system.cpp src/ecs/systems/test_system.h src/engine/shader_manager.h src/engine/shader_manager.cpp src/engine/model_manager.h src/engine/model_manager.cpp src/engine/terrain/chunk_generator.cpp src/engine/terrain/chunk_generator.h src/engine/terrain/chunk.h src/ecs/components/bubble_component.h src/ecs/systems/bubble_system.h src/ecs/components/plant_component.h src/ecs/systems/fish_system.h src/ecs/components/fish_component.h)

target_link_libraries(zombies ${OPENGL_gl_LIBRARY} ${GLFW_PATH} ${ASSIMP_PATH} ${IMGUI_PATH})

add_custom_command(TARGET zombies PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/shaders/ $<TARGET_FILE_DIR:zombies>/shaders)

add_custom_command(TARGET zombies PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/textures/ $<TARGET_FILE_DIR:zombies>/textures)

add_custom_command(TARGET zombies PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/models/ $<TARGET_FILE_DIR:zombies>/models)

add_custom_command(TARGET zombies PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_SOURCE_DIR}/libraries/export/assimp-vc140-mt.dll $<TARGET_FILE_DIR:zombies>/)