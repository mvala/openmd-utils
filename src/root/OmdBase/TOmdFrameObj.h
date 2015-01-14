//
// Class TOmdFrameObj
//
// TODO
//
// authors:
//          Martin Vala (mvala@saske.sk)
//

#ifndef ROOT_TOmdFrameObj
#define ROOT_TOmdFrameObj

#include <TObject.h>
#include <Rtypes.h>
#include <TGeoMatrix.h>

class TOmdFrameObj: public TObject {

public:
  TOmdFrameObj();
  virtual ~TOmdFrameObj();

  Int_t GetId() const;
  void SetId(Int_t id);

  Double32_t GetPosition(Int_t i=0) const;
  void SetPosition(Double32_t x, Double32_t y, Double32_t z);
  Double32_t GetVelocity(Int_t i=0) const;
  void SetVelocity(Double32_t x, Double32_t y, Double32_t z);
  Double32_t GetQuaternion(Int_t i=0) const;
  void SetQuaternion(Double32_t w, Double32_t x, Double32_t y, Double32_t z);

  TGeoRotation *GetRotationMatrix();
  void ApplyRotationMatrix(TGeoRotation *r);

  static Int_t SelfTest();

private:

  Int_t           fId;             // Id of object (openmd global id)
  Double32_t      fPosition[3];    // Position
  Double32_t      fVelocity[3];    // Velocity
  Double32_t      fQuaternion[4];  // Quaternion

  TGeoRotation   *fRotMatrix;      //! Rotation (converted from Quaternion)

  ClassDef(TOmdFrameObj, 1)

};

#endif
