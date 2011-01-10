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
    Box box;
public:
    BoxRule(Box b) : box(b) {}
        void UpdateBoids(std::vector<Boid*> boids) {
            for (std::vector<Boid*>::iterator itr = boids.begin();
                 itr != boids.end();
                 itr++) {
                Boid* b = *itr;
                Vector<3,float> pos = b->GetPosition();
                Vector<3,float> d = pos - box.GetCenter();
                Vector<3,float> s = box.GetSize();
                for (int i=0;i<3;i++) {
                    if (d[i] > s[i]) {                        
                        pos[i] = s[i];
                    } else if (-d[i] > s[i]) {
                        pos[i] = -s[i];
                    }                        
                }
                b->SetPosition(pos);
            }
        }
};
} // NS Animations
} // NS OpenEngine

#endif // _OE_BOX_RULE_H_
