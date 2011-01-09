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

namespace OpenEngine {
namespace Animations {

/**
 * Short description.
 *
 * @class CohersionRule CohersionRule.h ons/Boids/Animations/CohersionRule.h
 */
class CohersionRule : public IRule {
private:

public:
    void UpdateBoids(std::vector<Boid*> boids) {
        for (std::vector<Boid*>::iterator itr = boids.begin();
             itr != boids.end();
             itr++) {
            UpdateBoid(*itr,boids);
        }
    }
    void UpdateBoid(Boid* a, std::vector<Boid*> boids) {
        Vector<3,float> pc;
        int c = 0;
        for (std::vector<Boid*>::iterator itr = boids.begin();
             itr != boids.end();
             itr++) {
            Boid *b = *itr;
            if (b == a) continue;
            Vector<3,float> d = (b->GetPosition() - a->GetPosition());
            pc += b->GetPosition();
            c++;
        }
        pc = pc / max(c,1);
        a->AddVelocity((pc - a->GetVelocity()) / 100.0);
        
    }
    
};
} // NS Animations
} // NS OpenEngine

#endif // _OE_COHERSION_RULE_H_
