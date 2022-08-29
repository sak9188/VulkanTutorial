# CMake 最低版本号要求

################################################################################ 
cmake_minimum_required(VERSION 3.20)

# 设置c++版本要求
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)

project(VulkanTutorial)

# 在生成的项目文件中使用文件夹。开启文件夹组织项
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# 使用Unicode字符集
###############################################################################
add_definitions("-DUNICODE -D_UNICODE")
add_compile_options(/utf-8)

# Unix上生成Clangd可识别的IncludePath json文件
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # does not produce the json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works

# 设置自定义CMake模块目录
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)

# 导入第三方库
# glfw
set(LIB_GLFW_DIR ${CMAKE_MODULE_PATH}/glfw-3.3.8)
add_subdirectory(${LIB_GLFW_DIR})
set_target_properties(glfw PROPERTIES FOLDER "Depends")
set(GLFW_INCLUDE_DIR ${LIB_GLFW_DIR}/include/)

# glm
add_subdirectory(${CMAKE_MODULE_PATH}/glm-0.9.9.8)

# 导入目标引擎库
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/source)

