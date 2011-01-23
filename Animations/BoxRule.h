// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------


#ifndef _OE_BOX_RULE_H_
#define _OE_BOX_RULE_H_

#include <Animations/IRule.h>

namespace OpenEngine {
namespace Animations {

/**
 * Short description.
 *
 * @class BoxRule BoxRule.h ons/Boids/Animations/BoxRule.h
 */
class BoxRule : public IRule {
private:
    Vector<3,float> startPoint;
    Vector<3,float> endPoint;
    float boxSpeed;
    float boxDist;
public:
    BoxRule(Vector<3,float> s, Vector<3,float> e) 
        : IRule("Box")
        , startPoint(s)
        , endPoint(e) 
        , boxSpeed(10.0)
        , boxDist(10.0){}

    void ReloadProperties(Utils::PropertyTreeNode* pn) {
        startPoint = pn->GetPath("box.start", startPoint);
        endPoint = pn->GetPath("box.end", endPoint);
        boxSpeed = pn->GetPath("box.speed", boxSpeed);
        boxDist = pn->GetPath("box.dist", boxDist);
    }

    void UpdateBoids(std::vector<Boid*> boids) {
        for (std::vector<Boid*>::iterator itr = boids.begin();
             itr != boids.end();
             itr++) {
            Boid* b = *itr;
            Vector<3,float> p = b->GetPosition();
            Vector<3,float> v;

            if ((p[0] - startPoint[0]) < boxDist) {
                v[0] = boxSpeed;
            } else if ((endPoint[0] - p[0]) < boxDist ) {
                v[0] = -boxSpeed;
            }
            if ((p[1] - startPoint[1]) < boxDist) {
                v[1] = boxSpeed;
            } else if ((endPoint[1] - p[1]) < boxDist ) {
                v[1] = -boxSpeed;
            }
            if ((p[2] - startPoint[2]) < boxDist) {
                v[2] = boxSpeed;
            } else if ((endPoint[2] - p[2]) < boxDist ) {
                v[2] = -boxSpeed;
            }
            b->AddVelocity(v);

        }
    }
};
} // NS Animations
} // NS OpenEngine

#endif // _OE_BOX_RULE_H_
