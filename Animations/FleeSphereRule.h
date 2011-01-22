// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#ifndef _FLEE_SPHERE_RULE_H_
#define _FLEE_SPHERE_RULE_H_

#include <Animations/FleeRule.h>
#include <Scene/TransformationNode.h>

namespace OpenEngine {
namespace Animations {

using namespace Scene;

/**
 * Short description.
 *
 * @class FleeSphereRule.h FleeSphereRule.h.h ons/Boids/Animations/FleeSphereRule.h.h
 */
class FleeSphereRule : public FleeRule {
private:
    float radius;
    float scareFactor;

public:
    // Flee from sphere.
    FleeSphereRule(TransformationNode* fleeFromTrans, float radius = 100.0, float scare = 1.0) 
        : FleeRule(fleeFromTrans)
        , radius(radius)
        , scareFactor(scare){}


    ~FleeSphereRule() {}


    void ReloadProperties(Utils::PropertyTreeNode pn) {
        //        radius = pn.GetPath("flee.radius", 100.0);
        //        scareFactor = pn.GetPath("flee.scare", 1.0);
    }

    void SetRadius(float radius) {
        this->radius = radius;
    }

    void UpdateBoids(std::vector<Boid*> boids) {

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
