cmake_minimum_required( VERSION 3.1 )

project( raytracer-by-hailey )

find_package( OpenGL REQUIRED )

include_directories( ${OPENGL_INCLUDE_DIRS} )

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )

add_subdirectory( glfw )

if( MSVC )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

set( RAYTRACER-BY-HAILEY-SRC
     main.cpp
        vec3.h
        ray.h
        cameraSpec.h
        sphere.h
        collisionData.h
        hittableObject.h
        matrix3x3.h
        mesh.h
        cube.h
        mesh.cpp
        material.cpp
        material.h
        collisionData.cpp
        hittableObject.cpp
        boundingBox.cpp
        boundingBox.h
        plyImport.cpp
        plyImport.h
        sampler.cpp
        sampler.h
        scene.cpp
        scene.h
        utils.cpp
        utils.h
)
     
add_executable( raytracer-by-hailey WIN32 ${RAYTRACER-BY-HAILEY-SRC} )
target_link_libraries( raytracer-by-hailey ${OPENGL_LIBRARIES} glfw )
if( MSVC )
    if(${CMAKE_VERSION} VERSION_LESS "3.6.0") 
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'raytracer-by-hailey' as StartUp Project in Visual Studio.\n" )
    else()
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT raytracer-by-hailey )
    endif()
endif()
