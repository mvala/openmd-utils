#ifndef TOmdSelectorExample_H
#define TOmdSelectorExample_H

#include <TTree.h>
#include <TSelector.h>

class TTree;
class TOmdFrame;
class TH1D;

class TOmdSelectorExample: public TSelector {

public:

    TOmdSelectorExample(TTree *tree = 0);
    virtual ~TOmdSelectorExample();

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
    TH1D  *fHist;

ClassDef(TOmdSelectorExample, 1)


};

#endif
