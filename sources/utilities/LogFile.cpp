
#include <ctime>
#include <cstdarg>
#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ofstream;

#include <iosfwd>
#include <iterator>
#include <iosfwd>
#include <ios>
using std::ios;
using std::ios_base;

#include "LogFile.h"

//singleton pointer
LogFile* LogFile::s_pTheLog = NULL;

//set singleton pointer

void LogFile::SetLog(LogFile *pTheLog) {
    //ensure that there is not already an application
    if (s_pTheLog != NULL) {
        //more than one application!
        std::cerr << "**** ERRORE: Si sta tentando di instanziare piu' di un oggetto LogFile! ****" << std::endl;
        //exit
        exit(1);
    }
    //assign a value to the application
    s_pTheLog = pTheLog;
}

LogFile* LogFile::GetLog() {
    //return static pointer to application
    return (s_pTheLog);
}


bool LogFile::initLog(char* filename, const string &prj ) {
    
    //check for an application
    if (GetLog() == NULL) {
        //no application
        std::cerr << "**** WARNING: Nessun logfile e' stato instanziato! ****" << std::endl;
        //return error code
        return (-1);
    }
    
    enableLog();
    
    time_t ttime;
    tm* pCurTime;
    char cLogStart[128];

    //Store filename & type for later use
    sFilename = filename;

    //Get the current time
    time(&ttime);
    pCurTime = localtime(&ttime);
    strftime(cLogStart, 128, "<p style='font-size: 11px'>Log Started on %d/%m/%Y at %H:%M:%S</p>", pCurTime);

    //open the log file
    ofstream outfile(filename, ios::trunc);
    if (!outfile) return false; //something *really* went wrong

    outfile << "<html\n<title>Grafica Computazionale 2007/2008</title>\n"
            << "<body style='margin: 0 auto; padding-left: 20px; padding-top: 20px; font-size: 13px;'>\n"
            << "<h3 style='font-size: 16px;'>Grafica Computazionale A.A 2007/2008</h3>"
            << "studente: <em>Mirco Veltri</em>"
            << "<p style='font-size: 14px; color: #666666;'> (Logfile per il progetto <b>" << prj << "</b>)</p>"
            << cLogStart
            << "</body>\n</html>" << endl;

    //enable the log
    bEnabled = true;

    //close the log file
    outfile.close();
    return true;
}


void LogFile::writeLog(ELOG_COLORS color, char* szString, ...) {
    va_list va;
    time_t ttime;
    tm* pCurTime;

    char szParsedString[1024];
    char szLogTime[32];

    if (!bEnabled) {
        cout << "E' necessario abilitare il log" << endl;
        return;
    }

    //get time
    time(&ttime);
    pCurTime = localtime(&ttime);
    strftime(szLogTime, 32, "<pre>%H:%M:%S    ", pCurTime);

    //parse the given string
    va_start(va, szString);
    vsprintf(szParsedString, szString, va);
    va_end(va);

    //open the log file
    ofstream out(sFilename, ios_base::app);
    if (!out) return;

    out << "<font color='" << GetColor(color) << "'>" << szLogTime << szParsedString << "</pre></font>\n</body>\n</html>" << endl;
    out.close();
}

/*--------------------------------------------------------------
 * GetColor - private
 * Converte una costante in una stringa HTML colorata
 * Arguments:
 *        - color: il colore da ELOG_COLORS enumeration
 * Return Value:
 *        - C_like string: HTML color value
 * -------------------------------------------------------------*/
char* LogFile::GetColor(ELOG_COLORS color) {
    switch (color) {
        case LOG_SUCCESS:
            return "#4995B1";
            break;

        case LOG_FAILURE:
            return "#FF0000";
            break;

        case LOG_PLAINTEXT:
            return "#FF6600";
            break;

        case LOG_RENDERER:
            return "#4995B1";
            break;
    }

    return NULL;
}

