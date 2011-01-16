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
private:
    TransformationNode* fleeFromTrans;
    float radius;
    float scareFactor;

public:
    FleeRule(TransformationNode* fleeFromTrans, float radius = 100.0, float scare = 1.0) 
        : fleeFromTrans(fleeFromTrans)
        , radius(radius)
        , scareFactor(scare){}

    ~FleeRule() {}


    void ReloadProperties(Utils::PropertyTreeNode pn) {
        //        radius = pn.GetPath("flee.radius", 100.0);
        //        scareFactor = pn.GetPath("flee.scare", 1.0);
    }

    void SetTransformationToFleeFrom(TransformationNode* fleeFromTrans) {
        this->fleeFromTrans = fleeFromTrans;
    }

    void SetRadius(float radius) {
        this->radius = radius;
    }

    void UpdateBoids(std::vector<Boid*> boids) {
        //Vector<3,float> enemyPos = fleeFromTrans->GetPosition();
        Quaternion<float> r;
        Vector<3,float> enemyPos;
        Vector<3,float> s;
        fleeFromTrans->GetAccumulatedTransformations(&enemyPos,&r,&s);
        
        for (std::vector<Boid*>::iterator itr = boids.begin();
             itr != boids.end();
             itr++) {
        
            Boid* b = *itr;
            Vector<3,float> diff = b->GetPosition() - enemyPos;
            float dist = diff.GetLength();

            if( dist > radius ) continue;

            float danger = 1.0 - (dist / radius);
            Vector<3,float> fleeVec = diff * danger * scareFactor;
            b->AddVelocity(fleeVec);
        }
    }
    
};

} // NS Animations
} // NS OpenEngine

#endif
