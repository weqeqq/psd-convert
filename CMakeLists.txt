cmake_minimum_required(VERSION 3.28)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "-Wall" )

project(psd-convert)

set(INCLUDE ${CMAKE_SOURCE_DIR}/include)

set(SOURCE ${CMAKE_SOURCE_DIR}/src/)
set(SOURCE_TEST ${CMAKE_SOURCE_DIR}/test/)

include_directories(${INCLUDE})

set(SOURCES
    ${SOURCE}/psd_header.c
    ${SOURCE}/psd_cursor.c
    ${SOURCE}/psd_section.c
    ${SOURCE}/psd_conversion.c
    ${SOURCE}/psd_endian.c
    ${SOURCE}/psd_read.c)

set(HEADERS
    ${INCLUDE}/psd_cursor.h
    ${INCLUDE}/psd_result.h
    ${INCLUDE}/psd_types.h
    ${INCLUDE}/psd_header.h
    ${INCLUDE}/psd_section.h
    ${INCLUDE}/psd_buffer.h
    ${INCLUDE}/psd_conversion.h
    ${INCLUDE}/psd_endian.h
    ${INCLUDE}/psd_read.h)

set(PUBLIC_HEADER
    ${INCLUDE}/psd_convert.h)

set(SHARED_LIB ${PROJECT_NAME}-shared)
set(STATIC_LIB ${PROJECT_NAME}-static)

add_library(${STATIC_LIB} STATIC
            ${SOURCES} ${HEADERS})

add_library(${SHARED_LIB} SHARED
            ${SOURCES} ${HEADERS})

set_target_properties(${STATIC_LIB}
                        PROPERTIES
                        OUTPUT_NAME ${PROJECT_NAME}
                        PUBLIC_HEADER ${PUBLIC_HEADER})

set_target_properties(${SHARED_LIB}
                        PROPERTIES
                        OUTPUT_NAME ${PROJECT_NAME}
                        PUBLIC_HEADER ${PUBLIC_HEADER})

include(GNUInstallDirs)
install(TARGETS ${STATIC_LIB} ${SHARED_LIB}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

include(FindGit)
include(ExternalProject)
find_package(Git REQUIRED)

set(EXTERNAL_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/external)

enable_testing()

set(GTEST gtest)
set(GTEST_INSTALL_DIR ${EXTERNAL_INSTALL_DIR}/${GTEST})
set(GTEST_LIB ${GTEST_INSTALL_DIR}/lib/libgtest.a)
set(GTEST_INCLUDE ${GTEST_INSTALL_DIR}/include)

if(NOT EXISTS ${GTEST_INSTALL_DIR})

    ExternalProject_Add(
        ${GTEST}
        PREFIX              ${GTEST}

        GIT_REPOSITORY      https://github.com/google/googletest.git
        GIT_TAG             v1.14.0

        CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX:PATH=${GTEST_INSTALL_DIR}
        BUILD_COMMAND       ${CMAKE_COMMAND} --build <BINARY_DIR> --config Release)
endif()

set(TEST_SOURCES
    ${SOURCE_TEST}/endian.cpp
    ${SOURCE_TEST}/header.cpp
    ${SOURCE_TEST}/conversion.cpp
    ${SOURCE_TEST}/main.cpp)

add_executable(${PROJECT_NAME}-test)

target_sources(${PROJECT_NAME}-test PRIVATE
               ${TEST_SOURCES})

target_include_directories(${PROJECT_NAME}-test PRIVATE
                           ${INCLUDE}
                           ${GTEST_INCLUDE})

target_link_libraries(${PROJECT_NAME}-test PRIVATE
                      ${STATIC_LIB}
                      ${GTEST_LIB})

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-test)
