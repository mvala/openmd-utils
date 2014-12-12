//
// Class TOmdFrame
//
// TODO
//
// authors:
//          Martin Vala (mvala@saske.sk)
//

#include <TString.h>

#include "TOmdFrame.h"

ClassImp(TOmdFrame)

//_________________________________________________________________________________________________
TOmdFrame::TOmdFrame() :
		TObject() {
//
// Std constructor
//

}

//_________________________________________________________________________________________________
TOmdFrame::~TOmdFrame() {
//
// Destructor
//

}

//_________________________________________________________________________________________________
Int_t TOmdFrame::SelfTest() {

    Printf ("Testing 'TOmdFrame' ");

    Printf ("Testing 'TOmdFrame' [OK]");
    return 0;
}

