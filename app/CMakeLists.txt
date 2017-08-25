cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -DGLM_FORCE_SIZE_T_LENGTH")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLM_FORCE_RADIANS")

#INCLUDE_DIRECTORIES(src/main/cpp/fmod)

add_library( voicer
             SHARED
             src/main/cpp/EffectFix.cpp)

add_library( libfmod
             SHARED
             IMPORTED)
set_target_properties( libfmod
                       PROPERTIES IMPORTED_LOCATION
                       ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libfmod.so)
add_library( libfmodL
             SHARED
             IMPORTED)
set_target_properties( libfmodL
                       PROPERTIES IMPORTED_LOCATION
                       ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libfmodL.so)

find_library(log-lib
             log )

target_link_libraries( voicer
                       libfmod
                       libfmodL
                       ${log-lib} )