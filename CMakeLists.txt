cmake_minimum_required(VERSION 4.3.1)
project(rabbitlog LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(local.cmake)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS rbbl/*.cpp)
list(FILTER SOURCES EXCLUDE REGEX "main\\.cpp$")

if (UNIT_TEST)
    set(gtest_dir ${CMAKE_SOURCE_DIR}/test/google/api/googletest)
    add_subdirectory(${gtest_dir} ${CMAKE_BINARY_DIR}/googletest EXCLUDE_FROM_ALL)

    file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
        test/google/src/*.cpp
        test/google/interface/*.cpp
    )
    list(FILTER TEST_SOURCES EXCLUDE REGEX "google_test_main\\.cpp$")

    add_executable(${PROJECT_NAME} ${SOURCES} ${TEST_SOURCES} rbbl/src/main.cpp)
    target_compile_definitions(${PROJECT_NAME} PRIVATE UNIT_TEST)
    target_include_directories(${PROJECT_NAME} PRIVATE
        ${gtest_dir}/googletest/include
        ${gtest_dir}/googlemock/include
    )
    target_link_libraries(${PROJECT_NAME} PRIVATE gtest gmock)
else()
    add_executable(${PROJECT_NAME} ${SOURCES} rbbl/src/main.cpp)
    # _start:
    # compilation optimization
    target_compile_options(${PROJECT_NAME} PRIVATE -Os -ffunction-sections -fdata-sections)
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,--gc-sections -s)
    if (STATIC)
        target_link_options(${PROJECT_NAME} PRIVATE -static)
    endif()
    # _endof;
endif()

# don't modify atomic thread mode, it will cause performance loss
if (ATOMIC_THREAD_SPINLOCK_MODE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE USE_ATOMIC_THREAD_SPINLOCK_MODE=1)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    rbbl/include
    rbbl/api/lib
    rbbl/api
)

if (UNIT_TEST)
    target_include_directories(${PROJECT_NAME} PRIVATE
        test/google/src
        test/google/include
        test/google/interface
    )
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
