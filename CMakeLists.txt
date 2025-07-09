cmake_minimum_required(VERSION 3.10)
project(lvgl_cmake_linux_minimal_project)

cmake_policy(SET CMP0079 NEW)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)

set(CONFIG_LV_BUILD_EXAMPLES
    OFF
    CACHE BOOL "disable lvgl examples" FORCE)
set(CONFIG_LV_BUILD_DEMOS
    OFF
    CACHE BOOL "disable lvgl demos" FORCE)
set(CONFIG_LV_USE_THORVG_INTERNAL
    OFF
    CACHE BOOL "disable thorvg internal" FORCE)

add_subdirectory(lvgl)

target_link_libraries(lvgl PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
add_executable(lvgl_hello_world src/main.c)
target_include_directories(lvgl_hello_world PRIVATE lvgl ${SDL2_INCLUDE_DIRS}
                                                    ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(lvgl_hello_world PRIVATE lvgl)
