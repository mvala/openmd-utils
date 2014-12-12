//
// Class TOmdFrame
//
// TODO
//
// authors:
//          Martin Vala (mvala@saske.sk)
//

#ifndef ROOT_TOmdFrame
#define ROOT_TOmdFrame

#include <TObject.h>

class TOmdFrame: public TObject {

public:
	TOmdFrame();
	virtual ~TOmdFrame();

    static Int_t SelfTest();

private:

ClassDef(TOmdFrame, 1)


};

#endif
