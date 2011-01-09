// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------


#ifndef _OE_BOID_H_
#define _OE_BOID_H_

#include <Scene/TransformationNode.h>

namespace OpenEngine {
namespace Animations {

using namespace Scene;

/**
 * Short description.
 *
 * @class Boid Boid.h ons/Boids/Animations/Boid.h
 */
class Boid {
private:
    TransformationNode* transformationNode;
public:
    Boid(ISceneNode *n);
    TransformationNode* GetTransformationNode();
    void AddVelocity(Vector<3,float> v);
    void Update(float dt);
};

} // NS Animations
} // NS OpenEngine

#endif // _OE_BOID_H_
