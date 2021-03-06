# We can't tell which version of gtest we're building against and INSTANTIATE_TEST_CASE_P changed in
# a way that relies on a gcc extension to support backward-compatible code, So...
check_cxx_compiler_flag(-Wno-gnu-zero-variadic-macro-arguments MIRAL_COMPILE_WITH_W_NO_GNU_ZERO_VARIADIC_MACRO_ARGUMENTS)
check_cxx_compiler_flag(-Wno-pedantic MIRAL_COMPILE_WITH_W_NO_PEDANTIC)
if ("${CMAKE_CXX_COMPILER}" MATCHES ".*clang.*" AND MIRAL_COMPILE_WITH_W_NO_GNU_ZERO_VARIADIC_MACRO_ARGUMENTS)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-gnu-zero-variadic-macro-arguments") # clang
elseif(MIRAL_COMPILE_WITH_W_NO_PEDANTIC)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-pedantic") #gcc
endif()

include_directories(
    ${PROJECT_SOURCE_DIR}/src/miral
    ${MIRTEST_INCLUDE_DIRS}
    ${GMOCK_INCLUDE_DIR}
    ${GTEST_INCLUDE_DIR}
)

string(REPLACE "-fno-lto" "" NO_NO_LTO_FLAGS ${CMAKE_C_FLAGS})
set(CMAKE_C_FLAGS ${NO_NO_LTO_FLAGS})
string(REPLACE "-fno-lto" "" NO_NO_LTO_FLAGS ${CMAKE_CXX_FLAGS})
set(CMAKE_CXX_FLAGS ${NO_NO_LTO_FLAGS})

mir_add_wrapped_executable(miral-test NOINSTALL
    mru_window_list.cpp
    active_outputs.cpp
    command_line_option.cpp
    window_id.cpp
    runner.cpp
    select_active_window.cpp
    window_placement.cpp
    window_placement_anchors_to_parent.cpp
    window_placement_client_api.cpp
    window_properties.cpp
    drag_active_window.cpp
    modify_window_state.cpp
    modify_window_specification.cpp
    test_server.cpp         test_server.h
    test_window_manager_tools.h
    display_reconfiguration.cpp
    active_window.cpp
    raise_tree.cpp
    workspaces.cpp
    drag_and_drop.cpp
    client_mediated_gestures.cpp
    window_info.cpp
)

target_link_libraries(miral-test
    ${GTEST_BOTH_LIBRARIES}
    ${GMOCK_LIBRARIES}
    miral
    miral-internal
    mir-test-assist
)

add_test(miral-test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/miral-test)
