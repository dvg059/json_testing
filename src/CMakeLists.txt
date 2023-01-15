#howto: build.
#build/cmake ../src
# -  access this CMakelists.txt file to create a make file in build dir

#build/make	
# - executes the makefile created by cmake, creates the exe(LeetCode.exe)
#-------------------------------------------- 
cmake_minimum_required(VERSION 3.10)

add_library(
	json_rd_wr_lib STATIC
	json_rd_wr.cpp
	cjson_mngr.cpp
  ../json/jsoncpp.cpp
)

include_directories("../include" "../json")


# set the project name
project(JSON_RD_WR_PROJ VERSION 1.0.0)

# LeetCode.exe: add_executable(name_of_exe_output, src_file1 src_file2, ...) 
add_executable(JsonRdWr json_rd_wr.cpp )

# needed for linking the libray (say-hello) that we created
# exe that needs library - leet_code_lib
# how to lingk it: PRIVATE (very important)
# library were linkging to: say-hello form add_library up above
# target_link_libraries(name_of_exe_exe, link_type, name_of_library)
target_link_libraries(JsonRdWr PRIVATE json_rd_wr_lib)
