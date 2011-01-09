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
#include <Logging/Logger.h>

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
    float maxSpeed;
public:
    SpeedRule() : minSpeed(30.0), maxSpeed(100.0) {}

    void ReloadProperties(Utils::PropertyTreeNode pn) {
        minSpeed = pn.GetPath("speed.min", 30.0);
        maxSpeed = pn.GetPath("speed.max", 100.0);

    }
    void UpdateBoids(std::vector<Boid*> boids) {
        for (std::vector<Boid*>::iterator itr = boids.begin();
             itr != boids.end();
             itr++) {
            Boid* b = *itr;
            Vector<3,float> vel = b->GetVelocity();
            float speed = vel.GetLength();
            if (speed < 0.001) continue;
            if (speed < minSpeed)
                b->AddVelocity((vel / speed) * minSpeed);
            else if (speed > maxSpeed) {
                b->AddVelocity(-(vel / speed) * (speed - maxSpeed));
            }
        }
    }
};
} // NS Animations
} // NS OpenEngine

#endif // _OE_SPEED_RULE_H_
