#ifndef __CINT__
#include <TProof.h>
#include <TChain.h>
#include <TFileCollection.h>
#endif
void DumpRoot(const char *input="test.txt", const char *dsName="omd") {

  TFileCollection *fc = new TFileCollection();
  fc->AddFromFile(input);

  TProof *p = TProof::Open("");
  p->SetParallel(1);

  p->RegisterDataSet(dsName, fc, "O");
  p->VerifyDataSet(dsName);

  p->UploadPackage("OmdBase.par");
  p->EnablePackage("OmdBase.par");

  TOmdInputSelector *sel = new TOmdInputSelector();
  sel->SetOutputDir("/tmp");
//  sel->SetDrawOption("ogl");

  Long64_t numEvents = 1e10;
//  numEvents = 10;
  p->Process(dsName,sel,"",numEvents);

//  TChain *ch = new TChain("omdTree","Omd Tree");
//  ch->AddFile("/home/mvala/FeroMagnetics/Taiwan/01_RigidBody/02_Test/Ico.root");
//  ch->SetProof();
//  ch->Process(sel,"",numEvents);

}
