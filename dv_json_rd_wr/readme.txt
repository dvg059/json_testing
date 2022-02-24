This directory(dv_rd_wr_json), contains source and build insturctions to create dv_rd_wr_json.exe
json:               directory for 3rd party json packackage, used in the json file processing.
include:            include dir for source code.
docs:               Document for Json files used in testing.
readme.txt:         This readme file`
cjson_mngr.cpp:     CPP Source for cjson file mngr object, handles all json parsing and io. 
dv_json_rd_wr.cpp:  CPP source used for feeding files into cjson_mngr and controlling options
dv_rd_wr_json.exe:  compiled executeable.
MY_REPORT.TXT       default file name for report file ouput, 
JSON_PROCESS_LOG.txt    Log file for created everytime dv_rd_wr_json.exe is run. Details the processing of the json file input and report file output.

--------------------------------
how to build.
get code from git:
    - git commit -m "removing utest_json_rd_wr.exe"
build exe:
    - MakeFile: make -f MakeFile
    -creates dv_json_rd_wr.exe

Sample Execute:
    - ./dv_json_rd_wr <JSON file to parse>,  <PROCESS LOG>
    - ./dv_json_rd_wr.exe docs/input01.json MYLOGFILE
    - ./dv_json_rd_wr.exe docs/input01.json

---------------------------------


--------------------------------
Feedback 

1: He didn’t create any tool chain to build this application.  This is different from the requirement, and he didn’t explain why. 
2: The organizing of the code is misleading, third party shouldn’t be in the ‘dist’ folder. 
3: The code itself is not clear. For example, no sufficient comments, 

4: mixed using of the naming conventions (snake case and camel case). 
5: The solution is not optimized, there are lots of hard coded constants without explanation.

how to execute:
./dv_rd_wr_json.exe docs/input.json  
        // input file is  docs/input.json, output: is def ault file MY_REPORT.TXT

 ./dv_rd_wr_json.exe docs/input01.json new_report_name.txt
        // input file is  docs/input01.json, output: is default file new_report_name.txt  
--------------------------------
Overview:
    The application takes in json input file upon start (see how to execute) it will attempt to process the json file and create a report file using the format 
    in docs/readme.md.
    The application will create a log file (JSON_PROCESS_LOG) which will detail the json file parsing and report file.
    The application will only process fully qualified entries in the given log files.
    The manditory 4  entries:
        1  A known module name ("CTA", "MR", "CTP", "ICH", "ASPECTS")
        2: A boolean value for rulesEngineEnabled (true, false) 	
        3: A boolean value for rulesEngineTriggered (true, false)
        4: A non zero length string value for siteName i.e("Southern California Community Hospital")

    Unknown json entries are ignored.
    Valid json entries are added to the report vector.
    The objects in the report vector is then used to create the final output report.
