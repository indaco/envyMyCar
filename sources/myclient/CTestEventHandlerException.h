#ifndef _CTESTEVENTHANDLEREXCEPTION_H
#define	_CTESTEVENTHANDLEREXCEPTION_H

#include <stdexcept>
using std::runtime_error;


/* class: CTestEventHandlerException
 *
 *  Evita che la finestra SDL possa essere creata con dimensioni pari a 0, lanciando una eccezzione di tipo runtime_error
 */
class CTestEventHandlerException :public runtime_error {
public:
   CTestEventHandlerException() : runtime_error("\n*** ERRORE: Si sta cercando di inizializzare la finestra con una o entrambe le dimensioni a 0!") {};
};


#endif	/* _CTESTEVENTHANDLEREXCEPTION_H */

