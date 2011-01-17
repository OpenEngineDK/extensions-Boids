// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------


#ifndef _OE_MULTI_GOTO_RULE_H_
#define _OE_MULTI_GOTO_RULE_H_

#include <Animations/IRule.h>

namespace OpenEngine {
namespace Animations {

/**
 * Short description.
 *
 * @class MultiGotoRule MultiGotoRule.h ons/Boids/Animations/MultiGotoRule.h
 */
class MultiGotoRule : public IRule {
private:
    float magnitude;
    vector<Vector<3,float> > positions;
public:
    MultiGotoRule() : magnitude(0.1) {

    }

    void ReloadProperties(Utils::PropertyTreeNode pn) {
        if (pn.HaveNode("multigoto")) {
            Utils::PropertyTreeNode mgn = pn.GetNode("multigoto");
            if (mgn.HaveNode("positions")) {            
                positions.clear();
                Utils::PropertyTreeNode posNode = mgn.GetNode("positions");
                unsigned int num = posNode.GetSize();
                for (unsigned int i=0; i<num; i++) {
                    Vector<3,float> p = posNode.GetNode(i).Get<Vector<3,float> >();
                    positions.push_back(p);
                }
            }
        }
        magnitude = pn.GetPath("multigoto.magnitude", magnitude);
    }

    void UpdateBoids(std::vector<Boid*> boids) {
        int i=0;
        if (positions.size() == 0) return;
        for (std::vector<Boid*>::iterator itr = boids.begin();
             itr != boids.end();
             itr++) {
            Boid* a = *itr;
            
            Vector<3,float> h = positions[i++ % positions.size()];
            
            a->AddVelocity((h - a->GetPosition()) * magnitude);

        }
    }


};
} // NS Animations
} // NS OpenEngine

#endif // _OE_MULTI_GOTO_RULE_H_
