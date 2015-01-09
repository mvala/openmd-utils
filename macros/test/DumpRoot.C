#ifndef __CINT__
#include <TProof.h>
#include <TFileCollection.h>
#endif
void DumpRoot(const char *input="test.txt", const char *dsName="omd") {

  TFileCollection *fc = new TFileCollection();
  fc->AddFromFile(input);


  TProof *p = TProof::Open("");

  p->RegisterDataSet(dsName, fc, "O");
  p->VerifyDataSet(dsName);

  p->UploadPackage("OmdBase.par");
  p->EnablePackage("OmdBase.par");

  TOmdInputSelector *sel = new TOmdInputSelector();

  p->Process(dsName,sel);
}
