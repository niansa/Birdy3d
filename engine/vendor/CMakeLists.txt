target_sources(Birdy3d_engine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c
)

target_include_directories(Birdy3d_engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/stb_image
)

include(FetchContent)

find_package(Freetype)
if (FREETYPE_FOUND)
    target_include_directories(Birdy3d_engine PRIVATE ${FREETYPE_INCLUDE_DIRS})
else()
    FetchContent_Declare(
        freetype
        GIT_REPOSITORY   https://github.com/freetype/freetype
        GIT_TAG          VER-2-11-0
        CMAKE_CACHE_ARGS "-DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=ON"
    )

    FetchContent_MakeAvailable(freetype)
endif()

find_path(LIBRARY_GLM glm)
if(LIBRARY_GLM STREQUAL "LIBRARY_GLM-NOTFOUND")
    FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm
        GIT_TAG        master
    )

    FetchContent_MakeAvailable(glm)
    target_include_directories(Birdy3d_engine PUBLIC ${glm_SOURCE_DIR})
else()
    target_include_directories(Birdy3d_engine PUBLIC ${LIBRARY_GLM})
endif()

# TODO: uncomment find_library and change GIT_TAG once new-cursors-on-3.3-stable gets merged
#find_library(LIBRARY_GLFW glfw)
#if (NOT LIBRARY_GLFW)
    set(GLFW_BUILD_EXAMPLES OFF)
    set(GLFW_BUILD_TESTS OFF)

    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG        new-cursors-on-3.3-stable
    )

    FetchContent_MakeAvailable(glfw)
#endif()

find_library(LIBRARY_ASSIMP assimp)
if (NOT LIBRARY_ASSIMP)
    set(ASSIMP_BUILD_TESTS CACHE INTERNAL OFF)
    set(BUILD_SHARED_LIBS CACHE INTERNAL OFF)
    set(ASSIMP_BUILD_ASSIMP_TOOLS CACHE INTERNAL OFF)

    FetchContent_Declare(
        assimp
        GIT_REPOSITORY https://github.com/assimp/assimp
        GIT_TAG        v5.0.1
    )

    FetchContent_MakeAvailable(assimp)
endif()
