
This is directory has unit test that I developed and ran against the Json_mngr.
The dv_json_rd_wr application uses  a map to to actions module trigger combinations.
The map is preloaded with the knwon actions when the json_manger is created, these acations are stored in map.
The map keys consist of the module name combined with the engineEnabled, engineTriggered values.
A key that matches each json file entry is in the table. 
for example a module name of ASPECT with engineEnabled= true and engineTrigger = false becomes key ASPECTS10.
When that combination of mdoule name and variables is read in from a file, the application goes to the map and finds the approprate message for that key.
The message is stored in vector that is then processed as part fo the report

OVERVIEW SETUP:
1: retrive code repository from GIT.
    -   git clone  https://github.com/dvg059/json_testing.git
2: Make the test applicaiton.
    - make -f MakeFile, creates dv_json_unit_test.exe

3: Execute applciation to create a test report (UNIT_TEST_LOG) 
    - ./dv_json_unit_test.exe


Test include:
test_validate_json_rec(): 
 - test for known module name, 
 - test for boolean values for rulesEngineTriggered and rules engineEnabled
 - test for non null site name;

test_create_tbl_key
 - Create a  map key for the assocated records.
 - map key is  moduleName+ rulesEngineEnabled+rules + rulesEngineTriggered

test_validate_json_file T
Verifys the pasing of a json file with known values.
- json elements with missing required values.
- json elements with incorrect values.

how to build:
- g++ dv_json_unit_test.cpp ../dv_json_rd_wr/cjson_mngr.cpp ../dv_json_rd_wr/dist/jsoncpp.cpp -Iinclude/ -outest_json_rd_wr

how to run:
- /mnt/f/proj/dv_cpp_proj/dv_json_unit_test/utest_json_rd_wr
- utest_json_rd_wr

- expected out put in  UNIT_TEST_LOG
test_json_mngr_create: Start
CTOR CJsonMngr: 
DTOR CJsonMngr
SUCCESS test_json_mngr_create()


CTOR CJsonMngr: 
ERROR @line: 175 Error Message: rec.module is unknown: rec.module is:MRx
ERROR @line: 148 Error Message: SiteName Is Null: rec.siteName is:
LINE: 149	FAILD validation rec.siteName.length():0
test_validate_json_rec: START test known module names
DTOR CJsonMngr
SUCCESS test_validate_json_rec()


test_json_mngr_map START
CTOR CJsonMngr: 
test_json_mngr_map END
DTOR CJsonMngr
SUCCESS test_json_mngr_map()


test_validate_json_file START
CTOR CJsonMngr: 
Process: 220 Root : root.size() is:7
Process: 265 Success Passed JSON validation: rec.module is:CTA
Process: 273 Sucsess Passed record validation: rec.module is:CTA
value of rec.module is: 	CTA
value of rec.rulesEngineEnabled is: 	1
value of rec.rulesEngineTriggered is: 	0
value of rec.siteName is: 	North California Community Hospital
value of rec.msg is: 	Negative CT Angiography result at
value of rec.loudTone is: 	0
Process: 279 Success rec Added to report queue: rec.module is:CTA
Process: 265 Success Passed JSON validation: rec.module is:MR
Process: 273 Sucsess Passed record validation: rec.module is:MR
value of rec.module is: 	MR
value of rec.rulesEngineEnabled is: 	1
value of rec.rulesEngineTriggered is: 	0
value of rec.siteName is: 	Southern California Community Hospital
value of rec.msg is: 	Negative MR at
value of rec.loudTone is: 	0
Process: 279 Success rec Added to report queue: rec.module is:MR
Process: 265 Success Passed JSON validation: rec.module is:MR
Process: 273 Sucsess Passed record validation: rec.module is:MR
value of rec.module is: 	MR
value of rec.rulesEngineEnabled is: 	1
value of rec.rulesEngineTriggered is: 	0
value of rec.siteName is: 	Southern California Community Hospital
value of rec.msg is: 	Negative MR at
value of rec.loudTone is: 	0
Process: 279 Success rec Added to report queue: rec.module is:MR
ERROR @line: 228 Error Message: To few Rule Names: propNames.size() is:3
Process: 265 Success Passed JSON validation: rec.module is:xCTA
ERROR @line: 175 Error Message: rec.module is unknown: rec.module is:xCTA
ERROR @line: 269 Error Message: Failed Validation: rec.module is:xCTA
Process: 265 Success Passed JSON validation: rec.module is:ASPECTS
Process: 273 Sucsess Passed record validation: rec.module is:ASPECTS
value of rec.module is: 	ASPECTS
value of rec.rulesEngineEnabled is: 	1
value of rec.rulesEngineTriggered is: 	1
value of rec.siteName is: 	EASTERN California Community Hospital
value of rec.msg is: 	Low ASPECTS score at
value of rec.loudTone is: 	1
Process: 279 Success rec Added to report queue: rec.module is:ASPECTS
ERROR @line: 244 Error Message: Missing Required Rule Name: propNames.size() is:4
DTOR CJsonMngr
SUCCESS test_validate_json_file()
