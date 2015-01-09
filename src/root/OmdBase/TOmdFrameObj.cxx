//
// Class TOmdFrameObj
//
// TODO
//
// authors:
//          Martin Vala (mvala@saske.sk)
//

#include <TString.h>


#include "TOmdFrameObj.h"

ClassImp(TOmdFrameObj)

//_________________________________________________________________________________________________
TOmdFrameObj::TOmdFrameObj() :
TObject(), fId(0) {
  //
  // Std constructor
  //

}

//_________________________________________________________________________________________________
TOmdFrameObj::~TOmdFrameObj() {
  //
  // Destructor
  //

}

//_________________________________________________________________________________________________
Int_t TOmdFrameObj::SelfTest() {

  Printf ("Testing 'TOmdFrameObj' ");

  Printf ("Testing 'TOmdFrameObj' [OK]");
  return 0;
}

//_________________________________________________________________________________________________
Int_t TOmdFrameObj::GetId() const {
  return fId;
}

//_________________________________________________________________________________________________
void TOmdFrameObj::SetId(Int_t id) {
  fId = id;
}

//_________________________________________________________________________________________________
void TOmdFrameObj::SetPosition(Double32_t x, Double32_t y, Double32_t z) {
  fPosition[0] = x;
  fPosition[1] = y;
  fPosition[2] = z;
}


//_________________________________________________________________________________________________
Double32_t TOmdFrameObj::GetPosition(Int_t i) const {
  return (i<3)?fPosition[i]:0;
}

//_________________________________________________________________________________________________
void TOmdFrameObj::SetQuaternion(Double32_t w, Double32_t x, Double32_t y, Double32_t z) {
  fQuaternion[0] = w;
  fQuaternion[1] = x;
  fQuaternion[2] = y;
  fQuaternion[3] = z;
}

//_________________________________________________________________________________________________
Double32_t TOmdFrameObj::GetQuaternion(Int_t i) const {
  return (i<4)?fQuaternion[i]:0;
}

//_________________________________________________________________________________________________
void TOmdFrameObj::SetVelocity(Double32_t x, Double32_t y, Double32_t z) {
  fVelocity[0] = x;
  fVelocity[1] = y;
  fVelocity[2] = z;
}


//_________________________________________________________________________________________________
Double32_t TOmdFrameObj::GetVelocity(Int_t i) const {
  return (i<3)?fVelocity[i]:0;
}
