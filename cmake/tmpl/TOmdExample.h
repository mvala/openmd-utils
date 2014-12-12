//
// Class TOmdExample
//
// TODO
//
// authors:
//          Martin Vala (mvala@saske.sk)
//

#ifndef ROOT_TOmdExample
#define ROOT_TOmdExample

#include <TObject.h>

class TOmdExample: public TObject {

public:
	TOmdExample();
	virtual ~TOmdExample();

    static Int_t SelfTest();

private:

ClassDef(TOmdExample, 1)


};

#endif
