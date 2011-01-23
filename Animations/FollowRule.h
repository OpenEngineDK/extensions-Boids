// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#ifndef _FOLLOW_RULE_H_
#define _FOLLOW_RULE_H_

#include <Animations/IRule.h>
#include <Scene/TransformationNode.h>

namespace OpenEngine {
namespace Animations {

    using namespace Scene;

/**
 * Short description.
 *
 * @class FollowRule FollowRule.h ons/Boids/Animations/FollowRule.h
 */
class FollowRule : public IRule {
private:
    TransformationNode* followTrans;
    float magnitude;
public:
    FollowRule(TransformationNode* followTrans)
        : IRule("Follow"), followTrans(followTrans)
    , magnitude(0.01) {}
    ~FollowRule() {}

    void SetTransformationToFollow(TransformationNode* followTrans) {
        this->followTrans = followTrans;
    }
    void ReloadProperties(Utils::PropertyTreeNode* pn) {
        magnitude = pn->GetPath("follow.magnitude",magnitude);
    }

    void UpdateBoids(std::vector<Boid*> boids) {
        Vector<3,float> pos = followTrans->GetPosition();

        for (std::vector<Boid*>::iterator itr = boids.begin();
             itr != boids.end();
             itr++) {
            Boid* b = *itr;
            b->AddVelocity((pos - b->GetPosition()) * magnitude);
        }
    }
};

} // NS Animations
} // NS OpenEngine

#endif
