add_custom_target(lab4 ALL SOURCES main.cpp)

list(APPEND input_files varA.csv varB.csv varC.csv varD.csv varE.csv)
foreach(in_file IN LISTS input_files)
  add_custom_command(
    TARGET lab4 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_LIST_DIR}/${in_file}
    ${CMAKE_BINARY_DIR}/${in_file}
)
endforeach()

add_executable(lab4.out main.cpp)
target_link_libraries(lab4.out coma)