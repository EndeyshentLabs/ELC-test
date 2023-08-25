cmake_minimum_required(VERSION 3.14)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_C_STANDARD 99)

project(Elc-test C)

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
    -I${CMAKE_CURRENT_LIST_DIR}/..
    ${BUILDTYPE_FLAGS}
)

add_executable(elc-test
    main.c
)

target_compile_options(elc-test PUBLIC ${CFLAGS})

target_link_options(elc-test PRIVATE ${BUILDTYPE_FLAGS} -L${CMAKE_CURRENT_LIST_DIR}/.. -I${CMAKE_CURRENT_LIST_DIR}/..)

target_link_libraries(elc-test elc)
