// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------


#ifndef _OE_GOTO_RULE_H_
#define _OE_GOTO_RULE_H_

#include <Animations/IRule.h>

namespace OpenEngine {
namespace Animations {

/**
 * Short description.
 *
 * @class GotoRule GotoRule.h ons/Boids/Animations/GotoRule.h
 */
class GotoRule : public IRule {
private:
    Vector<3,float> home;
public:
    GotoRule(Vector<3,float> home) : home(home) {}
    void UpdateBoids(std::vector<Boid*> boids) {
        for (std::vector<Boid*>::iterator itr = boids.begin();
             itr != boids.end();
             itr++) {
            UpdateBoid(*itr,boids);
        }
    }
    void UpdateBoid(Boid* a, std::vector<Boid*> boids) {
        a->AddVelocity((home - a->GetPosition()) / 100.0);
    }

};
} // NS Animations
} // NS OpenEngine

#endif // _OE_GOTO_RULE_H_
