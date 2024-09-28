#initial setup
cmake_minimum_required(VERSION 3.14)

project(data_normalizer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # clangd

# Libraries
add_subdirectory(3rdparty/clickhouse-cpp)

#executable setup
set(SRC_FILES

  src/main.cpp
        src/table_worker.cpp src/table_worker.hpp src/clickhouse_manager.cpp src/internal_structs.h)
add_executable(${PROJECT_NAME} ${SRC_FILES}) 

target_include_directories(${PROJECT_NAME} 
                           PRIVATE 3rdparty/clickhouse-cpp
                           PRIVATE 3rdparty/clickhouse-cpp/contrlib/absi
                           PRIVATE 3rdparty/mINI/src)

target_link_libraries(${PROJECT_NAME}
                      PRIVATE clickhouse-cpp-lib)

#tests setup
