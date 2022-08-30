project(solis CXX)

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
# add_executable(solis ${PROJECT_SOURCES} ${PROJECT_HEADERS})
add_library(solis SHARED ${PROJECT_SOURCES} ${PROJECT_HEADERS})

find_package(Vulkan REQUIRED)

target_compile_definitions(
    solis
    PRIVATE
        SOLIS_API_EXPORT
)

target_link_libraries(
    solis
    PUBLIC
        glfw
        glm
        Vulkan::Vulkan
        ${ENGINE_LIB_BUILD_LIB}
)

target_include_directories(
    solis 
    PUBLIC
        ${ENGINE_SOURCE_PATH}
)

target_compile_definitions(
    solis
    PRIVATE
        VK_VALIDATION_REQURED
)

# 项目分租
set_target_properties(
    solis 
    PROPERTIES
        FOLDER "Runtime" 
)

set_target_properties(
    solis 
    PROPERTIES
        OUTPUT_NAME "solis"
)

# 指定输出路径
set_target_properties(solis PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_PATH}"
    LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_PATH}"
    RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_PATH}"
)
