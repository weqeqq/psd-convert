cmake_minimum_required(VERSION 3.28)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "-Wall" )

project(psd-convert)

set(INCLUDE ${CMAKE_SOURCE_DIR}/include)
set(INCLUDE_CLI ${INCLUDE}/cli)

set(SOURCE src/)
set(SOURCE_CLI ${SOURCE}/cli)

include_directories(${INCLUDE})

set(LIB_SOURCES
    ${SOURCE}/psd_header.c
    ${SOURCE}/psd_cursor.c
    ${SOURCE}/psd_section.c
    ${SOURCE}/psd_read.c)

set(LIB_HEADERS
    ${INCLUDE}/psd_cursor.h
    ${INCLUDE}/psd_result.h
    ${INCLUDE}/psd_types.h
    ${INCLUDE}/psd_header.h
    ${INCLUDE}/psd_section.h
    ${INCLUDE}/psd_read.h)

set(PUBLIC_HEADER
    ${INCLUDE}/psd_convert.h)

set(SHARED_LIB ${PROJECT_NAME}-shared)
set(STATIC_LIB ${PROJECT_NAME}-static)

add_library(${STATIC_LIB} STATIC
            ${LIB_SOURCES} ${LIB_HEADERS})

add_library(${SHARED_LIB} SHARED
            ${LIB_SOURCES} ${LIB_HEADERS})

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

set(LIBPNG libpng)
set(LIBPNG_INSTALL_DIR ${EXTERNAL_INSTALL_DIR}/${LIBPNG})
set(LIBPNG_LIB ${LIBPNG_INSTALL_DIR}/lib/libpng.so)
set(LIBPNG_INCLUDE ${LIBPNG_INSTALL_DIR}/include)

if(NOT EXISTS ${LIBPNG_INSTALL_DIR})

    ExternalProject_Add(
        ${LIBPNG}
        PREFIX              ${LIBPNG}

        GIT_REPOSITORY      https://github.com/pnggroup/libpng.git
        GIT_TAG             v1.6.43

        CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX:PATH=${LIBPNG_INSTALL_DIR}
        BUILD_COMMAND       ${CMAKE_COMMAND} --build <BINARY_DIR> --config Release)
endif()

set(CLI_SOURCES
    ${SOURCE_CLI}/main.c
    ${SOURCE_CLI}/psdcli_pathut.c
    ${SOURCE_CLI}/psdcli_argument.c
    ${SOURCE_CLI}/psdcli_extract.c
    ${SOURCE_CLI}/psdcli_write.c)

set(CLI_HEADERS
    ${INCLUDE_CLI}/psdcli_pathut.h
    ${INCLUDE_CLI}/psdcli_argument.h
    ${INCLUDE_CLI}/psdcli_extract.h
    ${INCLUDE_CLI}/psdcli_write.h)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
               ${CLI_SOURCES}
               ${CLI_HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE
                           ${INCLUDE}
                           ${INCLUDE_CLI}
                           ${LIBPNG_INCLUDE})

target_link_libraries(${PROJECT_NAME} PRIVATE
                      ${STATIC_LIB}
                      ${LIBPNG_LIB}
                      ${LIBWEBP_LIB})
