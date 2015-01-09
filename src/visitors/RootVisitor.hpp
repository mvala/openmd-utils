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
 
#ifndef VISITORS_ROOTVISITOR_HPP
#define VISITORS_ROOTVISITOR_HPP
#include <set>
#include <string>
#include <vector>

#include "visitors/BaseVisitor.hpp"
#include "primitives/StuntDouble.hpp"
#include "visitors/AtomData.hpp"
#include "selection/SelectionManager.hpp"
#include "selection/SelectionEvaluator.hpp"

#include <TTree.h>
#include "root/OmdBase/TOmdFrame.h"

namespace OpenMD {

  class SimInfo;

  class RootVisitor : public BaseVisitor{
  public:
    using BaseVisitor::visit; 
    
    RootVisitor(SimInfo* info, TOmdFrame *frame);
    
    RootVisitor(SimInfo* info, TOmdFrame *frame, const std::string& script);
    
    virtual void visit(Atom* atom);
    virtual void visit(DirectionalAtom* datom);
    virtual void visit(RigidBody* rb);

    virtual void update();

    virtual const std::string toString();
    
    void writeFrame(TTree *tree);
    void clear() {frame.clear();}

  protected:
    void internalVisit(StuntDouble* sd);
    bool isSelected(StuntDouble* sd);

  private:  
    std::string trimmedName(const std::string& atomType);

    SimInfo* info;
    SelectionManager seleMan;
    SelectionEvaluator evaluator; 
    TOmdFrame *omdFrame;
    std::vector<std::string> frame;
  };

}//namespace OpenMD
#endif //_ROOTVISITOR_H_
