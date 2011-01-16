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
#include <Math/RandomGenerator.h>

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
    Vector<3,float> velocity,prev;
    Vector<3,float> position;
    Quaternion<float> rotation;

public:
    Boid(ISceneNode *n, Math::RandomGenerator* rg);
    TransformationNode* GetTransformationNode();
    Vector<3,float> GetPosition() const;
    void SetPosition(Vector<3,float> p);
    Vector<3,float> GetVelocity();
    void AddVelocity(Vector<3,float> v);
    void Update(unsigned int dt);
};

} // NS Animations
} // NS OpenEngine

#endif // _OE_BOID_H_
