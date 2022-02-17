#ifndef DV_JSON_RD_WR_H_INCLUDED
#define DV_JSON_RD_WR_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include "json\json.h"

using namespace std;

#define SUCCESS 0       // No errors successfull func
#define FAIL_TO_PARSE 1 // json input file couldn't be read
#define FAIL_TO_READ 2  // INVALID FILE NAME
#define DEFAULT_JSON_FILE "docs/input.json"

typedef struct rules_rec {
    std::string module;
    bool rulesEngineEnabled;
    bool rulesEngineTriggered;
    std::string  siteName;

    std::string msg;
    bool loudTone;
} _rules_rec;

#define printDebug(x) cout <<"value of " << #x << " is: \t" << x << endl
//#define traceDebug(x) cout << "Line: " << __LINE__  <<" value of " << #x << " is: \t" << x << endl
#define printErrorMsg(x, msg) cout << "ERROR @line: " << __LINE__ << " Error Message: "<<  msg << ": " << #x << " is:" << x << endl
#define printProcessMsg(x,msg) cout << "Process: " << __LINE__ << " " <<  msg << ": " << #x << " is:" << x << endl

string get_json_file_to_process();
void print_json_rules_rec(rules_rec& rec);

class CJsonMngr {
private:
    string _fname;
    map<string, rules_rec> _map_table_rules;
    vector<rules_rec> _report_rec;
    vector<string> _vec_modules;   // list of acceptable module names


public:
    CJsonMngr();
    ~CJsonMngr();
    int validate_json_file(string fname, rules_rec &rec); 

    int reset_rules_rec(rules_rec& rec);// reset the assocated record to known values

    string create_tbl_key(rules_rec &rec); // create a key for 
    void show_map();
    bool get_rules_rec(string ky, rules_rec &rec);
    int add_rec_to_report(rules_rec rec);
    bool do_report(string report_name = "MY_REPORT.TXT");
    bool validate_json_rec(rules_rec rec);
    

};
#endif // end sentinel
