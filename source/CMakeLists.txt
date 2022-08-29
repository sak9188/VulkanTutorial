# 添加一些依赖源码
set(RUNTIME_PATH ${CMAKE_CURRENT_LIST_DIR}/runtime)
set(OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/output)

add_definitions(-DSOLIS_SO)

add_subdirectory(runtime)

add_subdirectory(test)
# add_subdirectory(test)
message(STATUS "SHARED_LINKER_FLAGS_DEBUG:    ${CMAKE_SHARED_LINKER_FLAGS_DEBUG}")
