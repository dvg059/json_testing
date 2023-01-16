# json_testing
application for reading and parsing json files using cpp.
dir structure:
1: Create a build dir and execute the "cmake build ../src/"
The output of the cmake file will be a make file in the build dir.
2: Execute the make file in the build dir . "build/make"
The output of the make file is and JsonRdWr.exe.
3: Run the JsonRdWr.exe and pass in the name of the json file to parse
build/JsownRdWr input.json. 
The JsonRdWr.exe will produce two files build/JSON_PROCESS.log, MY_REPORT.TXT.
The MY_REPORT.TXT is a report file that shows the results for the json file.
The JSON_PROCESS.log is the outpur/ report for the input json file.
Dir Structure:

- src: 
-- cpp source files created to read write source files.
--- cjson_mngr.cpp: file that reads and parses a json file.
--- CMakeLists.txt: cmake file. creates a make file. This Make file can be used to build
    the final exe.
    this make file should be invoke from a separte dir (i.e build/cmake  ../src/)
--- json_rd_wr.cpp: entry point for the application invokes the manager application

- include: 
-- include file created for the cpp files in src dir.
-- json_mngr.h header ffile for source file src/json_mngr.cpp
-- LOG>H header for logging the the application.

- json: 
Third party json package for parsing json objects

- utest:
-- dir for unit test source file.
-- CMakeLists.txt source file for cmake file. executed from separte dir build/cmake ../utest.
creates a make file(MakeFile) for creating the unit test application json_unit_test.exe.
build/make.
-- json_unit_test.cpp: unit test source file for creating unit tests.
