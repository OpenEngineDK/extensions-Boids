// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------


#ifndef _OE_FLOCK_H_
#define _OE_FLOCK_H_

#include <Animations/Boid.h>

namespace OpenEngine {
namespace Animations {
/**
 * Short description.
 *
 * @class Flock Flock.h ons/Boids/Animations/Flock.h
 */
class Flock {
private:
    ISceneNode *rootNode;
    std::vector<Boid*> boids;
    std::list<IRule*> rules;
public:
    ISceneNode* GetRootNode();
    void AddBoid(ISceneNode* node);
    void Update(float dt);
};

} // NS Animations
} // NS OpenEngine

#endif // _OE_FLOCK_H_
