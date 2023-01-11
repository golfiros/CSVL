set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(iterator_test iterator_test.c)
target_link_libraries(iterator_test csvl criterion)

add_executable(vector_test vector_test.c)
target_link_libraries(vector_test csvl criterion)

add_executable(stack_test stack_test.c)
target_link_libraries(stack_test csvl criterion)

add_custom_target(test 
  COMMAND echo "[----] Testing iterators"
  COMMAND iterator_test --always-succeed
  COMMAND echo "[----] Testing vectors"
  COMMAND vector_test --always-succeed
  COMMAND echo "[----] Testing stacks"
  COMMAND stack_test --always-succeed)
