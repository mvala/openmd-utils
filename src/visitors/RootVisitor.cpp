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
#include "selection/SelectionManager.hpp" 
#include "visitors/RootVisitor.hpp"
#include "primitives/DirectionalAtom.hpp"
#include "primitives/RigidBody.hpp"
#include "primitives/Molecule.hpp"
#include "brains/SimInfo.hpp"
#include "brains/Thermo.hpp"

namespace OpenMD {

  //------------------------------------------------------------------------//
  RootVisitor::RootVisitor(SimInfo *info) : BaseVisitor(), seleMan(info),
                                          evaluator(info), doPositions_(true),
                                          doVelocities_(false), 
                                          doForces_(false), doVectors_(false),
                                          doCharges_(false), 
                                          doElectricFields_(false) {
    this->info = info;
    visitorName = "RootVisitor";
    
    evaluator.loadScriptString("select all");
    
    if (!evaluator.isDynamic()) {
      seleMan.setSelectionSet(evaluator.evaluate());
    }
  }
  
  RootVisitor::RootVisitor(SimInfo *info, const std::string& script) :
    BaseVisitor(), seleMan(info), evaluator(info), doPositions_(true),
    doVelocities_(false), doForces_(false), doVectors_(false),
    doCharges_(false), doElectricFields_(false) {
    
    this->info = info;
    visitorName = "RootVisitor";

    evaluator.loadScriptString(script);

    if (!evaluator.isDynamic()) {
      seleMan.setSelectionSet(evaluator.evaluate());
    }
  }
    
  void RootVisitor::visit(Atom *atom) {
    // we ignore atoms
    return;
  }

  void RootVisitor::visit(DirectionalAtom *datom) {
    if (isSelected(datom))
      internalVisit(datom);
  }
  
  void RootVisitor::visit(RigidBody *rb) {
    if (isSelected(rb))
      internalVisit(rb);
  }
  
  void RootVisitor::update() {
    //if dynamic, we need to re-evaluate the selection
    if (evaluator.isDynamic()) {
      seleMan.setSelectionSet(evaluator.evaluate());
    }
  }
  
  void RootVisitor::internalVisit(StuntDouble *sd) {
    char                              buffer[1024];

    Vector3<RealType> p = sd->getPos();
    Quaternion<RealType> q = sd->getQ();
    
    std::string line;
    sprintf(buffer, "%d %e %e %e %e %e %e %e", sd->getGlobalIndex(), p.x(), p.y(), p.z(),
        q.w(), q.x(), q.y(), q.z());
    line += buffer;

    frame.push_back(line);
  }

  bool RootVisitor::isSelected(StuntDouble *sd) {
    return seleMan.isSelected(sd);
  }

  void RootVisitor::writeFrame(std::ostream &outStream, int id) {
    std::vector<std::string>::iterator i;
    char buffer[1024];
    
    if (frame.empty())
      std::cerr << "Current Frame does not contain any atoms" << std::endl;
    
    for( i = frame.begin(); i != frame.end(); ++i )
      outStream << id << " " << *i << std::endl;
  }
  
  std::string RootVisitor::trimmedName(const std::string&atomTypeName) {
    return atomTypeName.substr(0, atomTypeName.find('-'));
  }
  
  const std::string RootVisitor::toString() {
    char        buffer[65535];
    std::string result;
    
    sprintf(buffer,
            "------------------------------------------------------------------\n");
    result += buffer;
    
    sprintf(buffer, "Visitor name: %s\n", visitorName.c_str());
    result += buffer;
    
    sprintf(buffer,
            "Visitor Description: assemble the atom data and output root file\n");
    result += buffer;

    sprintf(buffer,
            "------------------------------------------------------------------\n");
    result += buffer;
    
    return result;
  }
  
} //namespace OpenMD