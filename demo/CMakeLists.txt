add_executable(main main.cpp)

target_include_directories(main PRIVATE ${PROJECT_ROOT_DIR}/qhm/include)
target_link_libraries(main PRIVATE qhm)

target_link_libraries(main PRIVATE sfml-graphics)
