/*
 * Copyright (c) 2005 The University of Notre Dame. All Rights Reserved.
 *
 * The University of Notre Dame grants you ("Licensee") a
 * non-exclusive, royalty free, license to use, modify and
 * redistribute this software in source and binary code form, provided
 * that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 * This software is provided "AS IS," without a warranty of any
 * kind. All express or implied conditions, representations and
 * warranties, including any implied warranty of merchantability,
 * fitness for a particular purpose or non-infringement, are hereby
 * excluded.  The University of Notre Dame and its licensors shall not
 * be liable for any damages suffered by licensee as a result of
 * using, modifying or distributing the software or its
 * derivatives. In no event will the University of Notre Dame or its
 * licensors be liable for any lost revenue, profit or data, or for
 * direct, indirect, special, consequential, incidental or punitive
 * damages, however caused and regardless of the theory of liability,
 * arising out of the use of or inability to use software, even if the
 * University of Notre Dame has been advised of the possibility of
 * such damages.
 *
 * SUPPORT OPEN SCIENCE!  If you use OpenMD or its source code in your
 * research, please cite the appropriate papers when you publish your
 * work.  Good starting points are:
 *                                                                      
 * [1]  Meineke, et al., J. Comp. Chem. 26, 252-271 (2005).             
 * [2]  Fennell & Gezelter, J. Chem. Phys. 124, 234104 (2006).          
 * [3]  Sun, Lin & Gezelter, J. Chem. Phys. 128, 234107 (2008).          
 * [4]  Kuang & Gezelter,  J. Chem. Phys. 133, 164101 (2010).
 * [5]  Vardeman, Stocker & Gezelter, J. Chem. Theory Comput. 7, 834 (2011).
 */
 
#include <iostream>
#include <fstream>
#include <string>

#include "applications/dump2Root/Dump2RootCmd.h"
#include "brains/Register.hpp"
#include "brains/SimCreator.hpp"
#include "brains/SimInfo.hpp"
#include "io/DumpReader.hpp"
#include "visitors/CompositeVisitor.hpp"
#include "visitors/RootVisitor.hpp"

#include <TFile.h>
#include <TTree.h>
#include "root/OmdBase/TOmdFrame.h"

using namespace OpenMD;

using namespace std;
int main(int argc, char* argv[]){
  
  gengetopt_args_info args_info;
  string dumpFileName;
  string rootFileName;

  //parse the command line option
  if (cmdline_parser (argc, argv, &args_info) != 0) {
    exit(1) ;
  }

  //get the dumpfile name and meta-data file name
  if (args_info.input_given){
    dumpFileName = args_info.input_arg;
  } else {
    cerr << "Does not have input file name" << endl;
    exit(1);
  }

  if (args_info.output_given){
    rootFileName = args_info.output_arg;
  } else {
    rootFileName = dumpFileName;
    rootFileName = rootFileName.substr(0, rootFileName.rfind(".")) + ".root";
  }

  //  parse md file and set up the system
  SimCreator creator;
  SimInfo* info = creator.createSim(dumpFileName, false);

  //create visitor list
  CompositeVisitor* compositeVisitor = new CompositeVisitor();

  TOmdFrame *omdFrame = new TOmdFrame();
  omdFrame->Init();
  //create rootVisitor
  RootVisitor* rootVisitor = new RootVisitor(info, omdFrame);
  compositeVisitor->addVisitor(rootVisitor, 200);

  //open dump file
  DumpReader* dumpReader = new DumpReader(info, dumpFileName);
  int nframes = dumpReader->getNFrames();

  // Create output file and tree
  TFile *omdFile = TFile::Open(rootFileName.c_str(),"RECREATE");
  TTree *omdTree = new TTree("omdTree","OpenMD tree");
  omdTree->Branch("omdFrame","TOmdFrame",&omdFrame);

  SimInfo::MoleculeIterator miter;
  Molecule::IntegrableObjectIterator  iiter;
  Molecule* mol;
  StuntDouble* sd;

  for (int i = 0; i < nframes; i += args_info.frame_arg){
    dumpReader->readFrame(i);
    cout << "Frame : " << i << endl;

    omdFrame->SetId(i);

    //update visitor
    compositeVisitor->update();

    //visit stuntdouble
    for (mol = info->beginMolecule(miter); mol != NULL;
         mol = info->nextMolecule(miter)) {

      for (sd = mol->beginIntegrableObject(iiter); sd != NULL;
           sd = mol->nextIntegrableObject(iiter)) {

        sd->accept(compositeVisitor);
      }
    }

    rootVisitor->writeFrame(omdTree);
    omdFrame->Clear();

    rootVisitor->clear();

  }//end for (int i = 0; i < nframes; i += args_info.frame_arg)

  delete compositeVisitor;
  delete info;

  omdTree->Write();
  omdFile->Close();
//  delete omdTree;
	return 0;
}
