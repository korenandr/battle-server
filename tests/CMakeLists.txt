enable_testing()

add_executable(
  battle_server_test
  GAME/GameTest.cpp
  GAME/UnitFactoryTest.cpp
  ${CMAKE_SOURCE_DIR}/src/GAME/Units/UnitFactory.cpp
  ${CMAKE_SOURCE_DIR}/src/GAME/Units/Unit.cpp
  ${CMAKE_SOURCE_DIR}/src/GAME/Units/Swordsman.cpp
  ${CMAKE_SOURCE_DIR}/src/GAME/Units/Hunter.cpp
)

# Set up include directories
target_include_directories(battle_server_test 
    PRIVATE 
        ${CMAKE_SOURCE_DIR}/src
)

# Link with Google Test
target_link_libraries(battle_server_test 
    PRIVATE 
        GTest::gtest_main 
        GTest::gmock_main
)

# Copy commands_example.txt to test directory
add_custom_command(
    TARGET battle_server_test
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/commands_example.txt
        ${CMAKE_CURRENT_BINARY_DIR}/commands_example.txt
    COMMENT "Copying commands_example.txt to test directory"
)

# Add tests
add_test(NAME battle_server_test COMMAND battle_server_test)