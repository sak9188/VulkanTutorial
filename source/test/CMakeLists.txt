# 添加一些依赖源码
project(testSolis CXX)

# 设置目录
set(PROJECT_INCLUDE_PATH ${CMAKE_CURRENT_LIST_DIR})
set(PROJECT_SOURCE_PATH ${CMAKE_CURRENT_LIST_DIR})

# 收集文件
file(GLOB_RECURSE PROJECT_SOURCES
    ${PROJECT_SOURCE_PATH}/*.cpp
)

file(GLOB_RECURSE PROJECT_HEADERS
    ${PROJECT_INCLUDE_PATH}/*.h
    ${PROJECT_INCLUDE_PATH}/*.hpp
)

# 对文件进行分组
source_group(TREE ${PROJECT_SOURCE_PATH}
    FILES ${PROJECT_SOURCES}
)

source_group(TREE ${PROJECT_INCLUDE_PATH}
    FILES ${PROJECT_HEADERS}
)

# 编译这个lib
add_executable(testSolis ${PROJECT_SOURCES} ${PROJECT_HEADERS})
# add_library(testSolis SHARED ${PROJECT_SOURCES} ${PROJECT_HEADERS})

find_package(Vulkan REQUIRED)

target_link_libraries(
    testSolis
    PUBLIC
        solis
)

target_include_directories(
    testSolis 
    PUBLIC
        ${RUNTIME_PATH}
)

# 项目分租
set_target_properties(
    testSolis 
    PROPERTIES
        FOLDER "App" 
)

set_target_properties(
    testSolis 
    PROPERTIES
        OUTPUT_NAME "testSolis"
)

# 指定输出路径
set_target_properties(testSolis PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_PATH}"
    LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_PATH}"
    RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_PATH}"
)
