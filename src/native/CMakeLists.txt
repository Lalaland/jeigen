cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)

set(EIGEN_DIRECTORY . CACHE STRING "Eigen directory.  The directory specified should have a subdirectory 'Eigen'.")
include_directories(${EIGEN_DIRECTORY})

find_package(JNI)

include_directories(${JNI_INCLUDE_DIRS})


add_library( jeigen SHARED jeigen_impl.cpp jeigen.cpp)
