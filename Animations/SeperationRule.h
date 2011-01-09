// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------


#ifndef _OE_SEPERATION_RULE_H_
#define _OE_SEPERATION_RULE_H_

#include <Animations/IRule.h>
#include <Logging/Logger.h>

namespace OpenEngine {
namespace Animations {

/**
 * Short description.
 *
 * @class SeperationRule SeperationRule.h ons/Boids/Animations/SeperationRule.h
 */
class SeperationRule : public IRule {
    float seperationDist;
public:
    SeperationRule() : seperationDist(20.0) {}

    void UpdateBoids(std::vector<Boid*> boids) {
        for (std::vector<Boid*>::iterator itr = boids.begin();
             itr != boids.end();
             itr++) {
            UpdateBoid(*itr,boids);
        }
    }
    void UpdateBoid(Boid* a, std::vector<Boid*> boids) {
        Vector<3,float> c(0,0,0);
        for (std::vector<Boid*>::iterator itr = boids.begin();
             itr != boids.end();
             itr++) {
            Boid *b = *itr;
            if (a == b) continue;
            Vector<3,float> d = (b->GetPosition() - a->GetPosition());
            float dist = d.GetLength();
            if (dist < seperationDist) {
                c = c - (d/seperationDist)*(seperationDist - dist);
            }
        }
        a->AddVelocity(c);
    }
    
};
} // NS Animations
} // NS OpenEngine

#endif // _OE_SEPERATION_RULE_H_
