project_add_library()

project_target_link_libraries(core)
project_target_link_libraries(GTest::gtest)

project_add_subdirectories()
