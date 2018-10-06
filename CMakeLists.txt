cmake_minimum_required (VERSION 3.0)
project (tinydb)

add_library(tinydb tiny.cc)

add_executable(gen generator.cc)

add_executable(dbtest dbtest.cc)
target_link_libraries(dbtest tinydb)

add_executable(ttest threaded_test.cc)
target_link_libraries(ttest tinydb pthread)

set(DATA_SIZE "10000000")
enable_testing()
add_test(test_gen gen ${DATA_SIZE})
add_test(test_run dbtest)
add_test(test_thread ttest ${DATA_SIZE})


