// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------


#ifndef _OE_COHERSION_RULE_H_
#define _OE_COHERSION_RULE_H_

#include <Animations/IRule.h>
#include <Logging/Logger.h>

namespace OpenEngine {
namespace Animations {

/**
 * Short description.
 *
 * @class CohersionRule CohersionRule.h ons/Boids/Animations/CohersionRule.h
 */
class CohersionRule : public IRule {
private:
    float magnitude;
public:
    CohersionRule() : magnitude(32.0) {}

    void ReloadProperties(Utils::PropertyTreeNode pn) {
        magnitude = pn.GetPath("cohersion.magnitude",32.0f);
    }

    void UpdateBoids(std::vector<Boid*> boids) {
        Vector<3,float> center;
        for (std::vector<Boid*>::iterator itr = boids.begin();
             itr != boids.end();
             itr++) {
            Boid* b = *itr;
            center += b->GetPosition();           
        }
        center /= boids.size();

        
        for (std::vector<Boid*>::iterator itr = boids.begin();
             itr != boids.end();
             itr++) {
            UpdateBoid(*itr, boids, center);
        }
    }
    void UpdateBoid(Boid* a, std::vector<Boid*> boids, Vector<3,float> pc) {
        a->AddVelocity((pc - a->GetPosition()) / magnitude);
        
    }
    
};
} // NS Animations
} // NS OpenEngine

#endif // _OE_COHERSION_RULE_H_
