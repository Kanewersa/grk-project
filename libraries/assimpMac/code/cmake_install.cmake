# Install script for directory: /Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Library/Developer/CommandLineTools/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/lib/libassimp.5.0.0.dylib"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/lib/libassimp.5.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.5.0.0.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.5.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      execute_process(COMMAND "/usr/bin/install_name_tool"
        -id "/usr/local/lib/libassimp.5.dylib"
        "${file}")
      execute_process(COMMAND /usr/bin/install_name_tool
        -delete_rpath "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/lib"
        "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -x "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/lib/libassimp.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -id "/usr/local/lib/libassimp.5.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/anim.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/aabb.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/ai_assert.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/camera.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/color4.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/color4.inl"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/config.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/defs.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/Defines.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/cfileio.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/light.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/material.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/material.inl"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/matrix3x3.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/matrix3x3.inl"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/matrix4x4.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/matrix4x4.inl"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/mesh.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/pbrmaterial.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/postprocess.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/quaternion.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/quaternion.inl"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/scene.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/metadata.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/texture.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/types.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/vector2.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/vector2.inl"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/vector3.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/vector3.inl"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/version.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/cimport.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/importerdesc.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/Importer.hpp"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/DefaultLogger.hpp"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/ProgressHandler.hpp"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/IOStream.hpp"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/IOSystem.hpp"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/Logger.hpp"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/LogStream.hpp"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/NullLogger.hpp"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/cexport.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/Exporter.hpp"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/DefaultIOStream.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/DefaultIOSystem.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/ZipArchiveIOSystem.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/SceneCombiner.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/fast_atof.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/qnan.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/BaseImporter.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/Hash.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/MemoryIOWrapper.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/ParsingUtils.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/StreamReader.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/StreamWriter.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/StringComparison.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/StringUtils.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/SGSpatialSort.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/GenericProperty.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/SpatialSort.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/SkeletonMeshBuilder.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/SmoothingGroups.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/SmoothingGroups.inl"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/StandardShapes.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/RemoveComments.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/Subdivision.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/Vertex.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/LineSplitter.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/TinyFormatter.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/Profiler.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/LogAux.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/Bitmap.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/XMLTools.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/IOStreamBuffer.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/CreateAnimMesh.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/irrXMLWrapper.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/BlobIOSystem.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/MathFunctions.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/Macros.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/Exceptional.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/ByteSwapper.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/Compiler/pushpack1.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/Compiler/poppack1.h"
    "/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

