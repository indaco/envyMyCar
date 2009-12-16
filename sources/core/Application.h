
//include guards
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

//include message handler(base class)
#include "MessageHandler.h"

/*
 * class: CApplication
 *
 * Derivata da CMessageHandler, ha come scopo quello di definire il flusso del programma che altrimenti
 * andrebbe nella funzione main. Non e' intesa per essere instanziata, di fatti il suo comportamento di default non fa praticamente nulla.
 * 
 * E' un passo intermedio tra CMessageHandler e CEventHandler.
 *
 * E' implementata come un Singleton.
 *
 */
class CApplication : public CMessageHandler {
private:
    //singleton pointer
    static CApplication* s_pTheApplication;

    //set singleton pointer
    static void SetApplication(CApplication* pTheApp);
public:
    /* constructor. CApplication */
    CApplication();

    //destructor
    virtual ~CApplication();

    /* 
     * method: OnInit
     * inizializzazione
     */
    virtual bool OnInit(int argc, char* argv[]);

    /* 
     * method: OnEvent
     * quando viene triggerato un evento
     */
    virtual void OnEvent(SDL_Event* pEvent);

    /* 
     * method: OnIdle
     * comportamento durante i cicli di idle
     */
    virtual void OnIdle();

   /* 
     * method: OnExit
     * all'uscita, prima di chiamare il distruttore
     */
    virtual void OnExit();

    /* 
     * method: Execute
     * esecuzione dell'applicazione
     */
    static int Execute(int argc, char* argv[]);

    /* 
     * method: GetApplication
     * get sel singleton application
     */
    static CApplication* GetApplication();
};

#endif //#ifndef __APPLICATION_H__
