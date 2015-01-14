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
    TObject(), fId(0), fRotMatrix(0) {
  //
  // Std constructor
  //

}

//_________________________________________________________________________________________________
TOmdFrameObj::~TOmdFrameObj() {
  //
  // Destructor
  //

  SafeDelete(fRotMatrix);

}

//_________________________________________________________________________________________________
Int_t TOmdFrameObj::SelfTest() {

  Printf("Testing 'TOmdFrameObj' ");

  Printf("Testing 'TOmdFrameObj' [OK]");
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
  return (i < 3) ? fPosition[i] : 0;
}

//_________________________________________________________________________________________________
void TOmdFrameObj::SetQuaternion(Double32_t w, Double32_t x, Double32_t y,
    Double32_t z) {
  fQuaternion[0] = w;
  fQuaternion[1] = x;
  fQuaternion[2] = y;
  fQuaternion[3] = z;
}

//_________________________________________________________________________________________________
Double32_t TOmdFrameObj::GetQuaternion(Int_t i) const {
  return (i < 4) ? fQuaternion[i] : 0;
}

//_________________________________________________________________________________________________
void TOmdFrameObj::SetVelocity(Double32_t x, Double32_t y, Double32_t z) {
  fVelocity[0] = x;
  fVelocity[1] = y;
  fVelocity[2] = z;
}

//_________________________________________________________________________________________________
Double32_t TOmdFrameObj::GetVelocity(Int_t i) const {
  return (i < 3) ? fVelocity[i] : 0;
}

//_________________________________________________________________________________________________
TGeoRotation *TOmdFrameObj::GetRotationMatrix() {

  if (!fRotMatrix)
    fRotMatrix = new TGeoRotation();

  ApplyRotationMatrix(fRotMatrix);

  return fRotMatrix;
}

//_________________________________________________________________________________________________
void TOmdFrameObj::ApplyRotationMatrix(TGeoRotation *r) {

  if (!r) return;

  Double_t matrix[9];

  Double_t w2 = fQuaternion[0] * fQuaternion[0];
  Double_t x2 = fQuaternion[1] * fQuaternion[1];
  Double_t y2 = fQuaternion[2] * fQuaternion[2];
  Double_t z2 = fQuaternion[3] * fQuaternion[3];

  matrix[0] = w2 + x2 - y2 - z2;
  matrix[1] = 2.0 * (fQuaternion[1] * fQuaternion[2] + fQuaternion[0] * fQuaternion[3]);
  matrix[2] = 2.0 * (fQuaternion[1] * fQuaternion[3] - fQuaternion[0] * fQuaternion[2]);

  matrix[3] = 2.0 * (fQuaternion[1] * fQuaternion[2] - fQuaternion[0] * fQuaternion[3]);
  matrix[4] = w2 - x2 + y2 - z2;
  matrix[5] = 2.0 * (fQuaternion[2] * fQuaternion[3] + fQuaternion[0] * fQuaternion[1]);

  matrix[6] = 2.0 * (fQuaternion[1] * fQuaternion[3] + fQuaternion[0] * fQuaternion[2]);
  matrix[7] = 2.0 * (fQuaternion[2] * fQuaternion[3] - fQuaternion[0] * fQuaternion[1]);
  matrix[8] = w2 - x2 - y2 + z2;

  r->SetMatrix(matrix);
  r->SetBit(TGeoMatrix::kGeoRotation);
}
