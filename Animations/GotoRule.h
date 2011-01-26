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
#include <Math/RandomGenerator.h>

namespace OpenEngine {
namespace Animations {

    using namespace Math;

/**
 * Short description.
 *
 * @class GotoRule GotoRule.h ons/Boids/Animations/GotoRule.h
 */
class GotoRule : public IRule {
private:
    Vector<3,float> home;
    RandomGenerator rg;
    float randomFactor;
    float magnitude;
public:
    GotoRule() 
        : IRule("Goto")
        , randomFactor(0.0)
        , magnitude(0.1) {}

    void ReloadProperties(Utils::PropertyTreeNode* pn) {
        home = pn->GetPath("goto.home", Vector<3,float>(0,0,0));
        randomFactor = pn->GetPath("goto.random", 0.0f);
        magnitude = pn->GetPath("goto.magnitude", 0.1f);
    }


    void UpdateBoids(std::vector<Boid*> boids) {
        for (std::vector<Boid*>::iterator itr = boids.begin();
             itr != boids.end();
             itr++) {
            UpdateBoid(*itr,boids);
        }
    }

    void UpdateBoid(Boid* a, std::vector<Boid*> boids) {
        Vector<3,float> h = home;
        h += Vector<3,float>(rg.UniformFloat(-1,1),
                             rg.UniformFloat(-1,1),
                             rg.UniformFloat(-1,1))*randomFactor;
        a->AddVelocity((h - a->GetPosition()) * magnitude);
    }

};
} // NS Animations
} // NS OpenEngine

#endif // _OE_GOTO_RULE_H_
