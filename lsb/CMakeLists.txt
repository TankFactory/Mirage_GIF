cmake_minimum_required(VERSION 3.20)

project(GIFLsb_native
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/../cmake/CompilerOptions.cmake)

if(NOT LIB_DIR)
    set(LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/../lib)
endif()

if(NOT EXECUTABLE_OUTPUT_PATH)
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/../bin)
endif()

if(NOT LIBRARY_OUTPUT_PATH)
    set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/../bin)
endif()

set(SOURCE_FILES "")
list(APPEND SOURCE_FILES
    ${CMAKE_CURRENT_LIST_DIR}/src/gif_lsb_enc.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/MimeTypes.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/mark.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gif_lsb_dec.cpp
)

set(INCLUDE_DIRS "")
list(APPEND INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${LIB_DIR}/include
)

set(COMPILE_DEFINITIONS "")
set(LINK_LIBRARIES "")

set(IMSQ_USE_NATIVE TRUE)
include(${LIB_DIR}/gif_enc/CMakeLists.txt)
include(${LIB_DIR}/image_sequence/CMakeLists.txt)
include(${LIB_DIR}/file_io/CMakeLists.txt)


if(${TARGET_LIB})
    add_library(giflsb SHARED ${SOURCE_FILES} ${CMAKE_CURRENT_LIST_DIR}/src/main_lib.cpp)

    target_include_directories(giflsb PRIVATE ${INCLUDE_DIRS})

    target_compile_options(giflsb PRIVATE ${GLOBAL_COMPILE_OPTIONS})

    target_link_options(giflsb PRIVATE ${GLOBAL_LINK_OPTIONS})

    target_compile_definitions(giflsb PRIVATE ${GLOBAL_COMPILE_DEFINITIONS} ${COMPILE_DEFINITIONS})
endif()

if(${TARGET_EXE})
    add_executable(GIFLsb-enc ${SOURCE_FILES}
        ${CMAKE_CURRENT_LIST_DIR}/src/main_enc.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/options_enc.cpp)
    add_executable(GIFLsb-dec ${SOURCE_FILES}
        ${CMAKE_CURRENT_LIST_DIR}/src/main_dec.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/options_dec.cpp)

    target_include_directories(GIFLsb-enc PRIVATE ${INCLUDE_DIRS})
    target_include_directories(GIFLsb-dec PRIVATE ${INCLUDE_DIRS})

    target_compile_options(GIFLsb-enc PRIVATE ${GLOBAL_COMPILE_OPTIONS})
    target_compile_options(GIFLsb-dec PRIVATE ${GLOBAL_COMPILE_OPTIONS})

    target_link_options(GIFLsb-enc PRIVATE ${GLOBAL_LINK_OPTIONS})
    target_link_options(GIFLsb-dec PRIVATE ${GLOBAL_LINK_OPTIONS})

    target_compile_definitions(GIFLsb-enc PRIVATE ${GLOBAL_COMPILE_DEFINITIONS} ${COMPILE_DEFINITIONS})
    target_compile_definitions(GIFLsb-dec PRIVATE ${GLOBAL_COMPILE_DEFINITIONS} ${COMPILE_DEFINITIONS})
endif()

