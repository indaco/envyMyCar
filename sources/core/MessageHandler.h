
#ifndef __MESSAGEHANDLER_H__
#define __MESSAGEHANDLER_H__

#include <SDL/SDL.h>

/* ------------------------------------------------------------------------------------------------------------- 
 * class: CMessageHandler
 *
 * E' una classe astratta che uso come base per le altre. Il suo scopo e' quello di fornire un meccanisco di comunicazione
 * tra le classi attraverso il concetto di gerarchia padre-figlio.
 *
 * Ogni oggetto di una classe del core (tranne gli oggetti di CApplication) ha un padre ed un certo numero di figli. 
 * CMessageHandler permette ad un oggetto figlio di inviare messaggi al padre e ricevere informazioni da esso, tramite
 * l'invio di messaggi seguiti da un numero di parametri opzionali che forniscono informazioni in piu' riguardo al messaggio.
 *
 *  Un altro scopo di questa classe e' quello di assegnare un ID univoco ad ogni messaggio. In questo modo confronto solo
 * l'ID del messaggio che e' stato inviato per identificarlo. L'ID viene assegnato tramite una funzione membro di tipo static.
 *
 *  NOTA: tutto il core e' basato su alcuni concetti presenti su diversi articoli presenti in rete di Martin Fowler per la parte
 *  strutturale e Ernest Pazera  per quanto riguarda SDL.
 *
 *
 * -------------------------------------------------------------------------------------------------------------*/

/*  
 * typedef: Uint32 MSGID
 * message ID
 */
typedef Uint32 MSGID;

/*  
 * typedef: void* MSGPARAM
 * message parameters
 */
typedef void* MSGPARM;


class CMessageHandler {
private:
    //parent message handler
    CMessageHandler* m_pmhParent;

    //next message id(static)
    static MSGID s_NextMSGID;
public:
    /* constructor: CMessageHandler */
    CMessageHandler(CMessageHandler* pmhParent);

    //destructor
    virtual ~CMessageHandler();

    /* method: SetParent */
    void SetParent(CMessageHandler* pmhNewParent);

    /* method: GetParent */
    CMessageHandler* GetParent();

    /* method: HasParent */
    bool HasParent();

    /* method: SendMessage */
    bool SendMessage(MSGID MsgID, MSGPARM Parm1 = NULL, MSGPARM Parm2 = NULL, MSGPARM Parm3 = NULL, MSGPARM Parm4 = NULL);

    /* method: setParent 
     *
     *  Processa i messaggi (virtual)
     */
    virtual bool OnMessage(MSGID MsgID, MSGPARM Parm1, MSGPARM Parm2, MSGPARM Parm3, MSGPARM Parm4);


    /* method: GetNextMSGID 
     *
     *  prende il prossimo message id (static)
     */
    static MSGID GetNextMSGID();

    /* method: MSGID_AddChild 
     *
     *  aggiunge un figlio (static msgid): Parm1=Parent, Parm2=Child
     */
    static MSGID MSGID_AddChild;

    /* method: MSGID_RemoveChild 
     *
     *  rimuove un figlio (static msgid): Parm1=Parent, Parm2=Child
     */
    static MSGID MSGID_RemoveChild;


    /* method: OnAddChild
     *
     *  aggiunge un gestore quando un figlio viene aggiunto (virtual)
     */
    virtual void OnAddChild(CMessageHandler* pmhChild);

    /* method: OnAddChild
     *
     *  rimuove il gestore quando un figlio viene rimosso (virtual)
     */
    virtual void OnRemoveChild(CMessageHandler* pmhChild);
};

#endif //#ifndef __MESSAGEHANDLER_H__
