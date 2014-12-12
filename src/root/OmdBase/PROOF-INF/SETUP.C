Int_t SETUP(TList *input = 0) {

	if (gSystem->Load("libOmdBase.so") < 0)
		return 1;

	// Set the include paths
	gROOT->ProcessLine(".include OmdBase");

	// Set our location, so that other packages can find us
	gSystem->Setenv("OmdBase_INCLUDE", "OmdBase");

	return 0;
}
