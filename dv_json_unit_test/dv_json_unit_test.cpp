// dv_json_unit_test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <fstream>
#include "..\dv_json_rd_wr\include\json_mngr.h"
#include "..\dv_json_rd_wr\include\json\json.h"
#include "..\dv_json_rd_wr\include\LOG.H"
#include <string>
#include <assert.h>

Clogger log("UNIT_TEST_LOG"); //redirect cout to a file;

// compare two records return true if  EQ, ELse return false
bool assert_rules_record(rules_rec r1, rules_rec r2)
{
	if (r1.module != r2.module)
		return false;
	if (r1.msg != r2.msg)
		return false;
	if (r1.loudTone != r2.loudTone)
		return false;
	if (r1.rulesEngineEnabled != r2.rulesEngineEnabled)
		return false;
	if (r1.rulesEngineTriggered != r2.rulesEngineTriggered)
		return false;

	return true;
}

/************************************************
 * test_create_tbl_key
 * -- Create a  map key for the assocated records.
 * -- map key is  moduleName+ rulesEngineEnabled+rules + rulesEngineTriggered
************************************************/
bool test_validate_json_rec()
{
	CJsonMngr jsonMngr;
	rules_rec rec;
	vector<string> modules = {"MR", "CTA", "CTP", "ICH",  "ASPECTS"};
    
	vector<string> sites ={"Southern California Community Hospital", "Northern California Community Hospital", "Hospital 3", "Hospital 4", ""};
	bool is_valid;

	// create a valid record : expect it to verify
	rec.module=modules[0];
	rec.siteName=sites[0];
	rec.rulesEngineEnabled=true;
	rec.rulesEngineTriggered=false;

	is_valid = jsonMngr.validate_json_rec(rec);
	if (!is_valid) {
		printErrorMsg(rec.module, "test_validate_json_rec FAILED");
		print_json_rules_rec(rec);
		return false;
	}

	// Test invalid record, with bad module
	rec.module=modules[0]+"x";
	rec.siteName=sites[0];
	rec.rulesEngineEnabled=true;
	rec.rulesEngineTriggered=false;
	is_valid = jsonMngr.validate_json_rec(rec);
	if (is_valid) {
		printErrorMsg(rec.module, "test_validate_json_rec FAILED");
		print_json_rules_rec(rec);
		return false;
	}

	// Test invalid record, with no site name, expected is_valid fasle
	rec.module=modules[0];
	rec.siteName="";
	rec.rulesEngineEnabled=true;
	rec.rulesEngineTriggered=false;

	is_valid = jsonMngr.validate_json_rec(rec);
	if (is_valid) {
		printErrorMsg(rec.module, "test_validate_json_rec FAILED");
		print_json_rules_rec(rec);
		return false;
	}

	// Test that all known module names are recognized.
	cout << "test_validate_json_rec: START test known module names" << endl; 
    for (int i = 0; i < modules.size(); i++)  {   
        rec.module = modules[i];
		rec.rulesEngineEnabled = true;
		rec.rulesEngineTriggered =  true;
		rec.siteName =  "new hospital site";

		is_valid = jsonMngr.validate_json_rec(rec);
		if (!is_valid){
			print_json_rules_rec(rec);
			printErrorMsg(rec.module, "test_validate_json_rec FAILED");
			return false;
		}
    }

	return  true;
}

/************************************************
 * test_create_tbl_key
 * -- Create a  map key for the assocated records.
 * -- map key is  moduleName+ rulesEngineEnabled+rules + rulesEngineTriggered
************************************************/
bool test_json_mngr_create()
{
	cout << "test_json_mngr_create: Start" << endl;
	CJsonMngr jsonMngr;
	rules_rec rec;

	string  expected_keys[]={"CTA10", "CTA00", "CTA11","MR00", "MR01", "MR11"}; // expected key results
	string module[]={"CTA", "CTA", "CTA","MR", "MR", "MR"};
	bool engine_enabled[]={true,false,true,false, false,true};		// engine enabled states
	bool engine_triggered[]={false,false,true,false,true,true};		// engine triggered states

	for (int i=0; i < 6; ++i)
	{
//		cout << "expected_key: " << expected_keys[i] << endl;

		rec.module= module[i];
		rec.rulesEngineEnabled=engine_enabled[i];
		rec.rulesEngineTriggered=engine_triggered[i];

		string ky = jsonMngr.create_tbl_key(rec);
		if (ky != expected_keys[i]){
			printErrorMsg(ky, "FAILED test_json_mngr_create: bad key returned");
			return false;
		}

	}

	return true;
}
/************************************************
 * Test the jsonMnger  map file, verify entries are correct
************************************************/
bool  test_json_mngr_map()
{
	cout << "test_json_mngr_map START" << endl;
	CJsonMngr jsonMngr;
	rules_rec rec;
	rec.msg="XXfare";
	rec.loudTone = true;

	jsonMngr.get_rules_rec("CTA00", rec );
	if (rec.msg != "New CT Angiography result at" && rec.loudTone != false)
	{
		printErrorMsg(rec.msg, "FAILED test_json_mngr_map: bad rec.msg returned");
		return false;
	}
//   CTA   	|         false        	|        N/A       	|    New CT Angiography result at {siteName}   	|        false       	|
//   CTA   	|         true         	|          false         	| Negative CT Angiography result at {siteName} 	|        false       	|
//   CTA   	|         true         	|          true          	| Positive CT Angiography result at {siteName} 	|        true        	|

    vector<string> keys = {"CTA00", "CTA01", "CTA10",  "CTA11"}; 
    vector<string> msgs = {"New CT Angiography result at", "New CT Angiography result at", 
						"Negative CT Angiography result at", "Positive CT Angiography result at"};

	vector<bool> tones =   {false,   false,   false,  true};

    for (int i = 0; i < keys.size(); i++)  {   
		// load the record for the given key
		jsonMngr.get_rules_rec(keys[i], rec );

		// Returned rec msg should match the expected msg
        if (rec.msg != msgs[i] ) {
			printErrorMsg(rec.msg, "FAILED test_json_mngr_map: bad rec.msg returned");
            return false;
        }

		// Returned rec loud  should match the expected msg
		if (rec.loudTone != tones[i]) {
			printErrorMsg(rec.loudTone, "FAILED test_json_mngr_map: bad rec.loudTone returned");
            return false;
		}
	}
	
	cout << "test_json_mngr_map END" << endl;
	return true;
}
/************************************************
 * 
************************************************/
bool test_validate_json_file()
{
	cout << "test_validate_json_file START" << endl;
	CJsonMngr jsonMngr;
	rules_rec rec;
	rec.module=""; 
	int ret = jsonMngr.validate_json_file("bad_json.json",rec);
	if (ret != 4){
		printErrorMsg(ret, "Failed tes_validate_json_file: ");
		return false;
	}
	return true;
}

/************************************************
 * 
************************************************/
int main()
{
	log.on();
	if ( test_json_mngr_create() ) {
		cout << "SUCCESS test_json_mngr_create()" << endl;
	} else {
		cout << "FAILED test_json_mngr_create()" << endl;
	}

	cout << "\n\n";
	if (test_validate_json_rec()) {
		cout << "SUCCESS test_validate_json_rec()" << endl;
	} else {
		cout << "FAILED test_validate_json_rec()" << endl;

	}

	cout << "\n\n";
	if ( test_json_mngr_map() ) 	{
		cout << "SUCCESS test_json_mngr_map()" << endl;
	} else {
		cout << "FAILED test_json_mngr_map()" << endl;

	}

	cout << "\n\n";
	if ( test_validate_json_file() ){
		cout << "SUCCESS test_validate_json_file()" << endl;
	} else {
		cout << "FAILED test_validate_json_file()" << endl;
	}

	log.off();
}
