#ifndef TOmdInputSelector_H
#define TOmdInputSelector_H

#include <TTree.h>
#include <TSelector.h>
#include <TH1D.h>

class TTree;
class TOmdFrame;

class TOmdInputSelector: public TSelector {

public:

  TOmdInputSelector(TTree *tree = 0);
  virtual ~TOmdInputSelector();

  virtual Int_t Version() const;
  virtual void Begin(TTree */*tree*/);
  virtual void SlaveBegin(TTree *tree);
  virtual void Init(TTree *tree);
  virtual Bool_t Notify();
  virtual Bool_t Process(Long64_t entry);
  virtual Int_t GetEntry(Long64_t entry, Int_t getall = 0);
  virtual void SlaveTerminate();
  virtual void Terminate();

private:

  TTree *fChain;                  //!pointer to the analyzed TTree or TChain
  TOmdFrame *fFrame;
  TH1D *fHist;

ClassDef(TOmdInputSelector, 1)

};

#endif
