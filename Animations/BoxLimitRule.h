// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------


#ifndef _OE_BOX_LIMIT_RULE_H_
#define _OE_BOX_LIMIT_RULE_H_

#include <Animations/IRule.h>

namespace OpenEngine {
namespace Animations {

/**
 * Short description.
 *
 * @class BoxLimitRule BoxLimitRule.h ons/Boids/Animations/BoxLimitRule.h
 */
class BoxLimitRule : public IRule {
private:
    Vector<3,float> startPoint;
    Vector<3,float> endPoint;
public:
    BoxLimitRule(Vector<3,float> s, Vector<3,float> e) 
        : IRule("BoxLimit")
        , startPoint(s)
        , endPoint(e) {}

    void ReloadProperties(Utils::PropertyTreeNode* pn) {
        startPoint = pn->GetPath("boxlimit.start", startPoint);
        endPoint = pn->GetPath("boxlimit.end", endPoint);        
    }

    void UpdateBoids(std::vector<Boid*> boids) {
         for (std::vector<Boid*>::iterator itr = boids.begin();
             itr != boids.end();
             itr++) {
            Boid* b = *itr;
            Vector<3,float> pos = b->GetPosition();
            Vector<3,float> npos = pos;
            for (int i=0;i<3;i++) {
                if (pos[i] < startPoint[i]) {
                    npos[i] = startPoint[i];
                } else if (pos[i] > endPoint[i] ) {
                    npos[i] = endPoint[i];
                }
            }
            b->SetPosition(npos);
        }
    }    
};
} // NS Animations
} // NS OpenEngine

#endif // _OE_BOX_LIMIT_RULE_H_
