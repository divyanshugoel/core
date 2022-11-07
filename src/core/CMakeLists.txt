project_add_library()

project_target_link_libraries(glm::glm)
project_target_link_libraries(GTest::gtest)
project_target_link_libraries(pthread)
project_target_link_libraries(trase)
project_target_link_libraries(spdlog::spdlog)

project_add_subdirectories()
