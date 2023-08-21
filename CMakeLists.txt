cmake_minimum_required(VERSION 3.14)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_C_STANDARD 99)

project(ELC C)

add_executable(
	elc-test
	main.c
	Token.c
	Lexer.c
	Parser.c
	Hashmap.c
)

target_include_directories(elc-test PUBLIC .)

target_compile_options(elc-test PUBLIC
    -Wall
    -Wextra
    -Werror
    -Wswitch-enum
    -fdiagnostics-color=always
    -pedantic
    $<$<CONFIG:DEBUG>:-O0 -g3 -ggdb3 -DDEBUG>
    $<$<CONFIG:RELEASE>:-O3>
)

target_link_options(elc-test PRIVATE
    $<$<CONFIG:DEBUG>:-O0 -g3 -ggdb3>
    $<$<CONFIG:RELEASE>:-O3>
)
