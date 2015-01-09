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
#include <TClonesArray.h>

class TOmdFrame: public TObject {

public:
  TOmdFrame();
  virtual ~TOmdFrame();

  virtual void Clear(Option_t *option ="");

  Int_t GetId() const;
  void SetId(Int_t id);

  void Init();
  void AddObject(Int_t id, Double32_t x, Double32_t y, Double32_t z,
      Double32_t vx, Double32_t vy, Double32_t vz,
      Double32_t qw, Double32_t qx, Double32_t qy, Double32_t qz);

  Int_t GetNObjects() const;
  TClonesArray *GetObjects() const;

  static Int_t SelfTest();

private:
  Int_t         fId;              // frame id
  Int_t         fNObjects;        // number of objects
  TClonesArray *fObjects;         //->array with all tracks

ClassDef(TOmdFrame, 1)

};

#endif
