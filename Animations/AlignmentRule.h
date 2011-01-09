// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------


#ifndef _OE_ALIGNMENT_RULE_H_
#define _OE_ALIGNMENT_RULE_H_

#include <Animations/IRule.h>

namespace OpenEngine {
namespace Animations {

/**
 * Short description.
 *
 * @class AlignmentRule AlignmentRule.h ons/Boids/Animations/AlignmentRule.h
 */
class AlignmentRule : public IRule {
private:

public:
    void UpdateBoids(std::vector<Boid*> boids) {
        Vector<3,float> collectiveVelocity;
        for (std::vector<Boid*>::iterator itr = boids.begin();
             itr != boids.end();
             itr++) {
            Boid* b = *itr;
            collectiveVelocity += b->GetVelocity();
        }
        collectiveVelocity /= boids.size();
        
        
        for (std::vector<Boid*>::iterator itr = boids.begin();
             itr != boids.end();
             itr++) {
            UpdateBoid(*itr,boids,collectiveVelocity);
        }
        
    }
    void UpdateBoid(Boid* a, std::vector<Boid*> boids, Vector<3,float> pv) {
        a->AddVelocity((pv - a->GetVelocity()) / 128.0);
        
    }

};
} // NS Animations
} // NS OpenEngine

#endif // _OE_ALIGNMENT_RULE_H_
