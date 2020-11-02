cmake_minimum_required(VERSION 2.8.11)
project(DebuggingTracing)

add_library(unlinkat_wrapper SHARED unlinkat_wrapper.c)
target_link_libraries(unlinkat_wrapper -ldl)

enable_testing()
add_test(test1 bash ../test1.sh)
add_test(test2 bash ../test2.sh)
