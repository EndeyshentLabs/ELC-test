cmake_minimum_required(VERSION 3.14)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_C_STANDARD 99)

project(ELC C)

set(BUILDTYPE_FLAGS
    $<$<CONFIG:DEBUG>:-O0 -g3 -ggdb3 -DDEBUG>
    $<$<CONFIG:RELEASE>:-O3>
)

set(CFLAGS
    -Wall
    -Wextra
    -Werror
    -Wswitch-enum
    -fdiagnostics-color=always
    -pedantic
    -I.
    ${BUILDTYPE_FLAGS}
)

add_library(elc
	Token.c
	Lexer.c
	Parser.c
	Hashmap.c
)

target_include_directories(elc PUBLIC .)

target_compile_options(elc PUBLIC ${CFLAGS})

target_link_options(elc PRIVATE
    ${BUILDTYPE_FLAGS}
)

add_custom_command(
    TARGET elc
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/libelc.a ${CMAKE_CURRENT_LIST_DIR}/libelc.a
)
