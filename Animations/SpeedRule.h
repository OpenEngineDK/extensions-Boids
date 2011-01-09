// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------


#ifndef _OE_SPEED_RULE_H_
#define _OE_SPEED_RULE_H_

#include <Animations/IRule.h>

namespace OpenEngine {
namespace Animations {

/**
 * Short description.
 *
 * @class SpeedRule SpeedRule.h ons/Boids/Animations/SpeedRule.h
 */
class SpeedRule : public IRule{
private:
    float minSpeed;
public:
    SpeedRule() : minSpeed(10.0) {}

    void UpdateBoids(std::vector<Boid*> boids) {
        for (std::vector<Boid*>::iterator itr = boids.begin();
             itr != boids.end();
             itr++) {
            Boid* b = *itr;
            Vector<3,float> vel = b->GetVelocity();
            float speed = vel.GetLength();
            if (speed < minSpeed)
                b->AddVelocity((vel / speed) * minSpeed);

        }
    }
};
} // NS Animations
} // NS OpenEngine

#endif // _OE_SPEED_RULE_H_
