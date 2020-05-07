find_package(ASSIMP REQUIRED)
#include_directories(${ASSIMP_INCLUDE_DIRS})

message("# ASSIMP_INCLUDE_DIRS" ${ASSIMP_INCLUDE_DIRS})
link_directories(${ASSIMP_LIBRARY_DIRS})
add_definitions(-DASSIMP_STATIC)
if(NOT ASSIMP_FOUND)
    message(ERROR " ASSIMP not found!")
else()
    add_definitions(-DWITH_ASSIMP)
endif()

