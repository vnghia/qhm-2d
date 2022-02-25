file(GLOB HEADER_FILES include/*.h)
file(GLOB SRC_FILES src/*.cpp)

add_library(qhm STATIC ${HEADER_FILES} ${SRC_FILES})

target_include_directories(qhm PRIVATE ${PROJECT_ROOT_DIR}/qhm/include)
