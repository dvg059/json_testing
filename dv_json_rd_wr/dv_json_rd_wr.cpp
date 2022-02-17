// dv_json_rd_wr.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

#include "include\json_mngr.h"
#include "include\json\json.h"
#include "include\LOG.H"

using namespace std;

Clogger log("JSON_PROCESS_LOG.txt"); //redirect cout to a file;

int main(int argc , char** argv) {
//===========================================
    cout << "Starting File Process" << argv[0];

    log.off();

    string fname = "";
    string report_name="";  // output file 
    
    if (argc > 1){
        std::cout << argv[1] << std::endl;
        fname = argv[1];
    } else {
        fname = get_json_file_to_process();
    }

    if (fname.empty()) {
        cout << "Stopping File Process" << endl;
        return FAIL_TO_READ;
    }
    if (argc > 2){
        report_name = argv[2];
    }
    cout << "Processing File: " << fname << endl;

    log.on();

    CJsonMngr jsonMngr;
    rules_rec rec;
    jsonMngr.validate_json_file(fname, rec);
    jsonMngr.do_report(report_name);

    cout << "logging off" << endl; 
    log.off();
    return 0;
}
