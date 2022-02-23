#include <iostream>
#include <fstream>

#include <map>
#include <string>
#include <iomanip>
#include <algorithm>
#include "include\json_mngr.h"
#include "json.h"
#include "include\LOG.H"

using namespace std;

extern Clogger log; //redirect cout to a file;

/***************************************
*
***************************************/
CJsonMngr::CJsonMngr()
{
    std::cout << "CTOR CJsonMngr: "  << endl;

    _vec_modules = {"MR", "CTA", "CTP", "ICH",  "ASPECTS"};


    rules_rec rec;
    rec.loudTone = false;
    rec.msg="New CT Angiography result at";

    _map_table_rules["CTA00"] = rec;
    _map_table_rules["CTA01"] = rec;

    rec.loudTone = false;
    rec.msg="Negative CT Angiography result at";
    _map_table_rules["CTA10"] = rec;

    rec.loudTone=true;
    rec.msg = "Positive CT Angiography result at";
    _map_table_rules["CTA11"] = rec;

    reset_rules_rec(rec);
    rec.loudTone = false;
    rec.msg = "New MR Result at";
    _map_table_rules["MR00"] = rec;
    _map_table_rules["MR01"] =  rec;

    rec.msg = "Negative MR at";
    rec.loudTone = false;
    _map_table_rules["MR10"] = rec;

    rec.msg = "Positive MR at";
    rec.loudTone = true;
    _map_table_rules["MR11"] = rec;


    reset_rules_rec(rec);
    rec.loudTone = false;
    rec.msg = "New CT Perfusion result at";
    _map_table_rules["CTP00"] = rec;
    _map_table_rules["CTP01"] = rec;

    rec.loudTone = false;
    rec.msg = "Negative CT Perfusion result at";
    _map_table_rules["CTP10"] = rec;

    rec.loudTone = true;
    rec.msg = "Positive CT Perfusion result at";
    _map_table_rules["CTP11"] = rec;

    reset_rules_rec(rec);
    rec.loudTone = false;
    rec.msg = "New hemorrhage module result at";
    _map_table_rules["ICH00"] = rec;
    _map_table_rules["ICH01"] = rec;

    rec.loudTone = false;
    rec.msg = "Negative hemorrhage module result at";
    _map_table_rules["ICH10"] = rec;

    rec.loudTone = true;
    rec.msg = "Positive hemorrhage module result at";
    _map_table_rules["ICH11"] = rec;

    reset_rules_rec(rec);
    rec.loudTone = false;
    rec.msg = "New ASPECTS score at";
    _map_table_rules["ASPECTS00"] = rec;
    _map_table_rules["ASPECTS01"] = rec;

    rec.loudTone = false;
    rec.msg = " High ASPECTS score at ";
    _map_table_rules["ASPECTS10"] = rec;
    
    rec.loudTone = true;
    rec.msg = "Low ASPECTS score at";
    _map_table_rules["ASPECTS11"] = rec;


//    show_map();
}

/***************************************
* display map
***************************************/
void CJsonMngr::show_map()
{  // showing contents:
   map<string, rules_rec>::iterator it = _map_table_rules.begin();

  std::cout << "_map_table_rules contains:\n";
  for (it =_map_table_rules.begin(); it != _map_table_rules.end(); ++it)
    std::cout << it->first << " => " << it->second.msg << '\n';
}
/***************************************
* retrive the record for given key:
- return true if recoed is found else return false
***************************************/
bool CJsonMngr::get_rules_rec(string ky, rules_rec &rec) 
{
   map<string, rules_rec>::iterator it = _map_table_rules.begin();
  it = _map_table_rules.find(ky);

  if (it != _map_table_rules.end()){
      rec.msg = it->second.msg;
      rec.loudTone = it->second.loudTone;
      return true;
  }

  return false;
}

/***************************************
***************************************/
CJsonMngr::~CJsonMngr()
{
    std::cout << "DTOR CJsonMngr" << endl;
}
/***************************************
* validate_json_rec(rules_rec rec)
* - verify the rules record meets validation criteria
* validation : 
* - known module name, 
* - boolean values for rulesEngineTriggered and rules engineEnabled
* - non null site name;
***************************************/
bool CJsonMngr::validate_json_rec(rules_rec rec)
{
    if (rec.siteName.length() <= 0){
        printErrorMsg(rec.siteName, "SiteName Is Null");
        return false;
    }

    if (rec.module.length() <= 0){
        printErrorMsg(rec.siteName, "Module Is Null");
        return false;
    }

    if (rec.rulesEngineEnabled != true && rec.rulesEngineEnabled != false) {
        printErrorMsg(rec.rulesEngineEnabled, "rec.rulesEngineEnabled Is Null");
        return false;
    }

    if (rec.rulesEngineTriggered != true && rec.rulesEngineTriggered != false) {
        printErrorMsg(rec.rulesEngineTriggered, "rulesEngineTriggered Is Null");
        return false;
    }

    for (unsigned i = 0; i < _vec_modules.size(); i++)  {   
        if (rec.module == _vec_modules[i]) {
            return true;
        }
    }

    printErrorMsg(rec.module, "rec.module is unknown");
    return false;

}
/***************************************
* add the record to the final reaport
* return the total number of records
***************************************/
int CJsonMngr::add_rec_to_report(rules_rec rec)
{
    _report_rec.push_back(rec); 
    return _report_rec.size();
}
/*************************************
 * print the record report using the fromat provided
 * ***********************************/
string center_string(int width, string& str) {
    int len = str.length();
    if(width < len) { return str; }

    int diff = width - len;
    int pad1 = diff/2;
    int pad2 = diff - pad1;
    return string(pad1, ' ') + str + string(pad2, ' ');
}

/***************************************
* parse the gvien json file into a rules_rec
* - return number of records parsed and ready for printing
***************************************/
int CJsonMngr::validate_json_file(string fname, rules_rec &rec)
{
    std::ifstream myFile(fname);

    Json::Value root;
    Json::Reader reader;

    if (!reader.parse(myFile, root, true)) {
        //for some reason it always fails to parse
        std::cout << "Failed to parse configuration\n"
            << reader.getFormattedErrorMessages();

        return FAIL_TO_PARSE;
    } else {
        vector<string> vec_rule_names = {"module", "rulesEngineEnabled", "rulesEngineTriggered", "siteName"};
        printProcessMsg(root.size(), "Root ");

        for (unsigned ii =0; ii < root.size(); ++ii) {
            Json::Value::Members propNames = root[ii].getMemberNames();


            if (vec_rule_names.size() > propNames.size() ) {
                    // All 4 module name are required 
                    printErrorMsg(propNames.size(), "To few Rule Names");
                    continue;
            }


            int found_rule_names = vec_rule_names.size();
            for (unsigned k =0; k < propNames.size(); ++k ) {
                //printProcessMsg(propNames[k], "property name");
                if (std::find(vec_rule_names.begin(), vec_rule_names.end(), propNames[k]) != vec_rule_names.end()) {
                        // The property name is found added remove it from the list.
                        --found_rule_names;
                }
            } // end for loop

            if  (found_rule_names > 0){
                // missing a rules property
                printErrorMsg(propNames.size(), "Missing Required Rule Name");
                continue;
            }
            
            reset_rules_rec(rec);
            rec.module = root[ii]["module"].asString();
            
            if (rec.module.empty()) {
                printErrorMsg(rec.module, "Missing Required Rule Name Module");
                continue;
            }

            rec.siteName = root[ii]["siteName"].asString();
            if (rec.siteName.empty() ) {
                printErrorMsg(rec.siteName, "Missing Required Rule Name siteName");
                continue;
            }

            rec.rulesEngineEnabled = root[ii]["rulesEngineEnabled"].asBool();
            rec.rulesEngineTriggered = root[ii]["rulesEngineTriggered"].asBool();
             //  All the req properies have been found, 
            printProcessMsg(rec.module,"Success Passed JSON validation");

            if ( !validate_json_rec(rec) ) {
                // This rec Failed validation, don't process 
                printErrorMsg(rec.module, "Failed Validation");
                continue;
            } else {
                // JSON properties are good, add the recorde to the table
                printProcessMsg(rec.module,"Sucsess Passed record validation");
                string key = create_tbl_key(rec);

                if ( get_rules_rec(key, rec) ){
                    print_json_rules_rec(rec);
                    add_rec_to_report(rec);
                    printProcessMsg(rec.module,"Success rec Added to report queue");

                } else {
                    printErrorMsg(rec.module, "No definition for module");
                    continue;
                }
            }
        }// end for loop 

    }  // end if

    return _report_rec.size();
}

/*************************************
 * print the record report using the fromat provided
 * ***********************************/
bool CJsonMngr::do_report(string report_name)
{
    if (report_name.empty()){
        report_name = "MY_REPORT.TXT";
    }

    Clogger report(report_name);
    log.off();
    report.on();

    // values for controlling format
    int module_width = 14;
    int rules_eng_width = 23;
    int rules_eng_trig_width = 27;
    int exptd_msg_width = 55;
    int exptd_tone_width = 23;
  //  int num_flds = 5;
    std::string sep = " |" ;

    vector<string> headers = {"Module","Rules engine enabled","Rules engine triggered","Expected message","Expected Loud tone"};
    vector<int> headerw = {module_width, rules_eng_width, rules_eng_trig_width, exptd_msg_width, exptd_tone_width}; // column width for each field

    //const int total_width = module_width + rules_eng_width + rules_eng_trig_width + (sep.size() * num_flds) + exptd_msg_width + exptd_tone_width;
    //const string line = sep + std::string( total_width-1, '-' ) + '|' 
    //int cur_pos =0;
    // Write column headings
    cout << "|";
    for (unsigned i=0; i<headers.size(); ++i)
    {
        string hdr = center_string(headerw[i], headers[i]);
        cout << hdr << sep;
    }
        cout << "\n";

    // Write field  sepeartors
    cout << "|";
    for (unsigned i=0; i<headerw.size(); ++i)
    {
        string feild_sp = ":" + string( headerw[i]-2, '-' ) + ':' ;
        cout << feild_sp << sep;
    }
    cout << "\n";

    // Write data fields;
    for (unsigned i= 0; i <_report_rec.size(); i++)
    {
        cout << "|";
        string mod_data =  center_string(module_width, _report_rec[i].module);
        cout << mod_data << sep;

        string bool_str = _report_rec[i].rulesEngineEnabled?"true":"false";
        string rules_eng_data =  center_string(rules_eng_width, bool_str);
        cout << rules_eng_data << sep;

        bool_str = _report_rec[i].rulesEngineTriggered ?"true":"false";
        string rules_eng_trig_data =  center_string(rules_eng_trig_width, bool_str);
        cout << rules_eng_trig_data << sep;

        string exptd_msg_data = _report_rec[i].msg + " " + _report_rec[i].siteName;
        exptd_msg_data = center_string(exptd_msg_width, exptd_msg_data);
        cout << exptd_msg_data << sep;

        bool_str = _report_rec[i].loudTone ?"true":"false";
        string loud_tone_data = center_string(exptd_tone_width, bool_str);
        cout << loud_tone_data << sep;

        cout << "\n";
    }
    return true;
}

/***************************************
*
***************************************/

/**************************************************
* reset rec elements to known values
**************************************************/
int CJsonMngr::reset_rules_rec(rules_rec& rec)
{
    rec.module.empty();
    rec.rulesEngineEnabled = false;
    rec.rulesEngineTriggered = false;
    rec.siteName.empty();

    rec.msg.empty();
    rec.loudTone=false;
    return SUCCESS;
}

/**************************************************
 * Create tble key from rules_rec
**************************************************/
string CJsonMngr::create_tbl_key(rules_rec &rec)
{
    map<string,rules_rec> rules_tbl;
    string engine_enabled = rec.rulesEngineEnabled?"1":"0";
    string engine_triggered = rec.rulesEngineTriggered?"1":"0";
    return( rec.module + engine_enabled + engine_triggered);

}


/***************************************
*
***************************************/
string get_json_file_to_process()
{
    string fname;
    string user_in;

    bool start_file_process = false;

    while (!start_file_process) {
        std::cout << "Enter Json File Name: " << fname;
        std::getline(std::cin, fname);

        std::cout << "JSON file to process " << fname << "\nSelect Q to QUIT, \n R to Renter: \n Enter to Continue" << endl;

        std::getline(std::cin, user_in);

        if (user_in == "R" || user_in == "r") {
            user_in.clear();
            std::cout << "Renter file name " << endl;
        }
        else if (user_in == "Q" || user_in == "q") {
            fname.clear();
            start_file_process = true;
        }
        else {
            start_file_process = true;
        }

    }
    return fname;
}

/***************************************
*
***************************************/
void print_json_rules_rec(rules_rec& rec)
{
    printDebug(rec.module);
    printDebug(rec.rulesEngineEnabled);
    printDebug(rec.rulesEngineTriggered);
    printDebug(rec.siteName);
    printDebug(rec.msg);
    printDebug(rec.loudTone);

}
