cmake_minimum_required(VERSION 3.14)
project(code)

add_executable(main main.c pcre.c)

if(UTF)
	add_definitions(-DUTF)
endif()

find_library(PCRE2_LIBRARIES NAMES pcre2 pcre2-8)
find_path(PCRE2_INCLUDE_DIRS pcre2.h)
add_custom_target(pcre2)

find_package(Curses REQUIRED)


include_directories(
        ${CURSES_INCLUDE_DIRS}
        ${PCRE2_INCLUDE_DIRS}
)
target_link_libraries(main ${CURSES_LIBRARIES} ${PCRE2_LIBRARIES})

