add_executable(fibonacci fibonacci.c)
target_link_libraries(fibonacci csvl)

add_executable(to-upper to_upper.c)
target_link_libraries(to-upper csvl)
