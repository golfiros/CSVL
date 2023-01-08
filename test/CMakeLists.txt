add_executable(unit_test unit_test.c)
target_link_libraries(unit_test csvl criterion)

add_custom_target(test COMMAND unit_test --always-succeed)
