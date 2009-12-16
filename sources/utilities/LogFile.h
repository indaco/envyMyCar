#ifndef _LOGFILE_H
#define	_LOGFILE_H

#include <iostream>
using std::boolalpha;

#include <string>
using std::string;

/* class: LogFile
 *
 * Questa classe opera uno stream su un file HTML usato come logfile.
 *
 * E' stata implementata come Singleton.
 */

/*
 * enumeration: ELOG_COLORS
 *
 * I colori associabili agli eventi da gestire con i log
 */
enum ELOG_COLORS {
    LOG_SUCCESS = 0,
    LOG_FAILURE,
    LOG_PLAINTEXT,
    LOG_RENDERER
};



class LogFile {
public:

    LogFile() : bEnabled(false), sFilename(0) {
        // set the log
        SetLog(this);
    }

    /*--------------------------------------------------------------
     *constructor: LogFile 
     *
     * Inizializza direttamete il log
     *
     * Arguments:
     *
     *        -szFilename: il nome del file da usare come logfile (scriverlo completo di estensione. Es. log.html)
     *
     * Return Value: 
     * 
     *          void
     *
     * -------------------------------------------------------------*/
    LogFile(char* szFilename, const string &prjName) : bEnabled(false), sFilename(0) {
        initLog(szFilename, prjName);
    }

    LogFile(const LogFile& orig) {
    }; // Costruttore di copia

    ~LogFile(void) {
    } // Distruttore


    /*--------------------------------------------------------------
     * method: initLog
     *
     * Inizializza il log su file HTML
     *
     * Arguments:
     *
     * szFilename: il nome del file HTML da usare come log
     *
     * Return Value:	un boolean: 
     * 
     *                          -true: inizializzazione effettuata con sccesso
     *
     *                         -false: inizializazzione fallita
     * -------------------------------------------------------------*/
    bool initLog(char* filename, const string &prj);


    /*--------------------------------------------------------------
     *  method: writeLog 
     *
     *  Scrive una stringa del colore specificato nel file
     *
     *  Arguments:
     *
     *        - color: il colore come elemento di ELOG_COLORS
     *
     *        - szString: una stringa in formato C-style da inviare al file di log
     *
     *  Return Value: 
     * 
     *          void
     *
     * -------------------------------------------------------------*/
    void writeLog(ELOG_COLORS color, char* sString, ...);

    /*--------------------------------------------------------------
     * method: enableLog 
     *
     * Abilita il log
     *
     * Arguments:	
     *
     *          none
     *
     * Return Value: 
     * 
     *          void
     *
     * -------------------------------------------------------------*/
    inline void enableLog(void) {
        bEnabled = true;
    }

    /*--------------------------------------------------------------
     * method: disableLog 
     *
     * Disabilita il log
     *
     * Arguments:	
     * 
     *          none
     *
     * Return Value: 
     * 
     *          void
     *
     * -------------------------------------------------------------*/
    inline void disableLog(void) {
        bEnabled = false;
    }

    /*--------------------------------------------------------------
     * Name: LogFile::IsEnabled 
     *
     * Controlla se il log è abilitata oppure no
     *
     * Arguments:	
     * 
     *          none
     *
     * Return Value:
     *
     *        - true: se il log è abilitato
     *
     *        - false: se il log è disabilitato
     *
     * -------------------------------------------------------------*/
    inline bool isEnabled(void) {
        return bEnabled;
    }

    //get singleton
    static LogFile *GetLog();

private:
    //singleton pointer
    static LogFile *s_pTheLog;
    //set singleton pointer
    static void SetLog(LogFile *pTheLog);

    char *sFilename;
    bool bEnabled;
    char *GetColor(ELOG_COLORS color);

};


#endif	/* _LOGFILE_H */

