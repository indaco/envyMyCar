#include "MessageHandler.h"

// inizializzazione di un membro statico
//next message id(static)
MSGID CMessageHandler::s_NextMSGID = 0;

//msgid: add child(static)
MSGID CMessageHandler::MSGID_AddChild = CMessageHandler::GetNextMSGID();

//msgid: remove child(static)
MSGID CMessageHandler::MSGID_RemoveChild = CMessageHandler::GetNextMSGID();

//constructor

CMessageHandler::CMessageHandler(CMessageHandler* pmhParent) :
//initialize parent to NULL
m_pmhParent(NULL) {
    //set parent
    SetParent(pmhParent);
}

//destructor

CMessageHandler::~CMessageHandler() {
    //set parent to NULL
    SetParent(NULL);
}

//set parent

void CMessageHandler::SetParent(CMessageHandler* pmhNewParent) {
    // questo oggetto ha un padre?
    if (HasParent()) {
        // comunica al padre che stiamo rimuovendo un figlio
        SendMessage(MSGID_RemoveChild, (MSGPARM) GetParent(), (MSGPARM)this);
    }

    // imposta un nuovo padre
    m_pmhParent = pmhNewParent;

    // l'ggetto ha un padre?
    if (HasParent()) {
        // comunica al padre che stiamo aggiungendo un figlio
        SendMessage(MSGID_AddChild, (MSGPARM) GetParent(), (MSGPARM)this);
    }
}

//get parent

CMessageHandler* CMessageHandler::GetParent() {
    // restituisce il padre
    return (m_pmhParent);
}

//has parent?

bool CMessageHandler::HasParent() {
    //return true if parent is non-null
    return (GetParent() != NULL);
}

//send message

bool CMessageHandler::SendMessage(MSGID MsgID, MSGPARM Parm1, MSGPARM Parm2, MSGPARM Parm3, MSGPARM Parm4) {
    // aspetta di processare il messaggio
    if (OnMessage(MsgID, Parm1, Parm2, Parm3, Parm4)) {
        // il messaggio e' stato processato
        return (true);
    } else {
        // il messaggio non e' stato processato
        //ccontrolla il padre
        if (HasParent()) {
            // il padre esiste, gli invio un messaggio
            return (GetParent()->SendMessage(MsgID, Parm1, Parm2, Parm3, Parm4));
        } else {
            // il padre non esiste e non posso pertanto processare il messeggio
            return (false);
        }
    }
}

//process message(pure virtual)

bool CMessageHandler::OnMessage(MSGID MsgID, MSGPARM Parm1, MSGPARM Parm2, MSGPARM Parm3, MSGPARM Parm4) {
    // processa ilmessaggio "aggiungi figlio"
    if (MsgID == MSGID_AddChild) {
        //conrolla che questo sia il padre
        if (this == (CMessageHandler*) Parm1) {
            // è il padre
            OnAddChild((CMessageHandler*) Parm2);
            return (true);
        } else {
            //non e' il pdre
            return (false);
        }
    } else
        // processa ilmessaggio "rimuovi figlio"
        if (MsgID == MSGID_RemoveChild) {
        // controlla che questo  il padre
        if (this == (CMessageHandler*) Parm1) {
            // è il padre
            OnRemoveChild((CMessageHandler*) Parm2);
            return (true);
        } else {
            // non è il padre
            return (false);
        }
    } else {
        // messaggio sconosciuto
        return (false);
    }
}

//get next message id(static)

MSGID CMessageHandler::GetNextMSGID() {
    // ritorna il messageid corrente ed incrementa il valorere
    return (s_NextMSGID++);
}

//add child handler

void CMessageHandler::OnAddChild(CMessageHandler* pmhChild) {
    //do nothing
}

//remove child handler

void CMessageHandler::OnRemoveChild(CMessageHandler* pmhChild) {
    //do nothing
}
