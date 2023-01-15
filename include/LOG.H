#pragma once

#include <iostream>     // std::streambuf, std::cout
#include <fstream>      // std::ofstream

//Logging module redirct the cout stream to a file  when logging is on.
//
class Clogger {
    std::streambuf *psbuf, *backup;
    std::ofstream filestr;
    std::string  _mylog;
    bool on_off;  // false logging is off, ture logging is on
public:
    Clogger(string fname = "mylog") {
        _mylog = fname;

    }
    bool off() {
        std::cout.rdbuf(backup);        // restore cout's original streambuf
        filestr.close();
        on_off = false;
        return on_off;                       // return 0 logging is off
    }
    bool on(){
        filestr.open (_mylog);

        backup = std::cout.rdbuf();     // back up cout's streambuf

        psbuf = filestr.rdbuf();        // get file's streambuf
        std::cout.rdbuf(psbuf);         // assign streambuf to cout
        on_off = true;
        return on_off;                    // return true logging is on
    }
    ~Clogger() {
        off();
     }
};