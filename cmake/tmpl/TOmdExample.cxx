//
// Class TOmdExample
//
// TODO
//
// authors:
//          Martin Vala (mvala@saske.sk)
//

#include <TString.h>

#include "TOmdExample.h"

ClassImp(TOmdExample)

//_________________________________________________________________________________________________
TOmdExample::TOmdExample() :
		TObject() {
//
// Std constructor
//

}

//_________________________________________________________________________________________________
TOmdExample::~TOmdExample() {
//
// Destructor
//

}

//_________________________________________________________________________________________________
Int_t TOmdExample::SelfTest() {

    Printf ("Testing 'TOmdExample' ");

    Printf ("Testing 'TOmdExample' [OK]");
    return 0;
}

