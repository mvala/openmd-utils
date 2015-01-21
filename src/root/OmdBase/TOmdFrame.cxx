//
// Class TOmdFrame
//
// TODO
//
// authors:
//          Martin Vala (mvala@saske.sk)
//

#include <TString.h>

#include <TVector3.h>
#include <TLorentzVector.h>
#include "TOmdFrameObj.h"

#include "TOmdFrame.h"

ClassImp(TOmdFrame)

//_________________________________________________________________________________________________
TOmdFrame::TOmdFrame() :
    TObject(), fId(0), fNObjects(0), fObjects(0) {
  //
  // Standard constructor
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
  //
  // Self test
  //

  Printf("Testing 'TOmdFrame' ");

  Printf("Testing 'TOmdFrame' [OK]");
  return 0;
}

//_________________________________________________________________________________________________
void TOmdFrame::Clear(Option_t* option) {
  //
  // Clear frame
  //

  fId = 0;
  fNObjects = 0;
  fObjects->Clear("C");
}

//_________________________________________________________________________________________________
void TOmdFrame::Init() {
  //
  // Initialization of frame
  //

  if (!fObjects)
    fObjects = new TClonesArray("TOmdFrameObj", 0);
}

//_________________________________________________________________________________________________
void TOmdFrame::AddObject(Int_t id, Double32_t x, Double32_t y, Double32_t z, Double32_t vx, Double32_t vy,
    Double32_t vz, Double32_t qw, Double32_t qx, Double32_t qy, Double32_t qz) {
  //
  // Adding Frame Object
  //

  TOmdFrameObj *obj = (TOmdFrameObj*) fObjects->ConstructedAt(fNObjects++);
  obj->SetId(id);
  obj->SetPosition(x, y, x);
  obj->SetVelocity(vx, vy, vz);
  obj->SetQuaternion(qw, qx, qy, qz);
}

//_________________________________________________________________________________________________
Int_t TOmdFrame::GetId() const {
  //
  // returns ID
  //

  return fId;
}

//_________________________________________________________________________________________________
void TOmdFrame::SetId(Int_t id) {
  //
  // Setting ID
  //

  this->fId = id;
}

//_________________________________________________________________________________________________
Int_t TOmdFrame::GetNObjects() const {
  //
  // returns number of objects
  //

  return fNObjects;
}

//_________________________________________________________________________________________________
TClonesArray* TOmdFrame::GetObjects() const {
  //
  // returns objects of TFrameObj
  //

  return fObjects;
}
