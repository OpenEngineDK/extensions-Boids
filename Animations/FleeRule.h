// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#ifndef _FLEE_RULE_H_
#define _FLEE_RULE_H_

#include <Animations/IRule.h>
#include <Scene/TransformationNode.h>

namespace OpenEngine {
namespace Animations {

using namespace Scene;

/**
 * Short description.
 *
 * @class FleeRule FleeRule.h ons/Boids/Animations/FleeRule.h
 */
class FleeRule : public IRule {
protected:
    TransformationNode* fleeFromTrans;

public:
    FleeRule(TransformationNode* fleeFromTrans)
        : fleeFromTrans(fleeFromTrans) {}

    ~FleeRule() {}


    void ReloadProperties(Utils::PropertyTreeNode pn) {
        //        radius = pn.GetPath("flee.radius", 100.0);
        //        scareFactor = pn.GetPath("flee.scare", 1.0);
    }

    void SetTransformationToFleeFrom(TransformationNode* fleeFromTrans) {
        this->fleeFromTrans = fleeFromTrans;
    }

    TransformationNode* GetTransformationToFleeFrom() {
        return fleeFromTrans;
    }

    void UpdateBoids(std::vector<Boid*> boids) {
    }
    
};

} // NS Animations
} // NS OpenEngine

#endif
