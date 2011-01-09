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
#include <Animations/IRule.h>
#include <Core/IListener.h>
#include <Core/EngineEvents.h>
#include <vector>

namespace OpenEngine {
namespace Animations {
/**
 * Short description.
 *
 * @class Flock Flock.h ons/Boids/Animations/Flock.h
 */
class Flock : public Core::IListener<Core::ProcessEventArg> {
private:
    ISceneNode *rootNode;
    std::vector<Boid*> boids;
    std::list<IRule*> rules;
public:
    Flock();
    ISceneNode* GetRootNode();
    void AddBoid(ISceneNode* node);
    void Handle(Core::ProcessEventArg arg);
    //void Update(float dt);
    
};

} // NS Animations
} // NS OpenEngine

#endif // _OE_FLOCK_H_
