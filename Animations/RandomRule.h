// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------


#ifndef _OE_RANDOM_RULE_H_
#define _OE_RANDOM_RULE_H_

#include <Animations/IRule.h>
#include <Math/RandomGenerator.h>

namespace OpenEngine {
namespace Animations {

/**
 * Short description.
 *
 * @class RandomRule RandomRule.h ons/Boids/Animations/RandomRule.h
 */
class RandomRule : public IRule {
private:
    float magnitude;
    Math::RandomGenerator rg;
public:
    RandomRule() 
        : IRule("Random")
        , magnitude(10.0) {
        rg.SeedWithTime();
    }
    void ReloadProperties(Utils::PropertyTreeNode* pn) {
        magnitude = pn->GetPath("random.magnitude", magnitude);
    }

    void UpdateBoids(std::vector<Boid*> boids) {
        for (std::vector<Boid*>::iterator itr = boids.begin();
             itr != boids.end();
             itr++) {
            Boid *b = *itr;
            Vector<3,float> rnd(rg.UniformFloat(-1,1),
                                rg.UniformFloat(-1,1),
                                rg.UniformFloat(-1,1));
            b->AddVelocity(rnd*magnitude);
        }
    }


};
} // NS Animations
} // NS OpenEngine

#endif // _OE_RANDOM_RULE_H_
