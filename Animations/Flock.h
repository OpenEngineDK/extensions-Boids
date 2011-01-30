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
#include <Math/RandomGenerator.h>
#include <Utils/PropertyTree.h>
#include <Utils/PropertyTreeNode.h>

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
    Math::RandomGenerator* randomGenerator;
    Utils::PropertyTreeNode* pNode;

public:
    Flock();
    ISceneNode* GetRootNode();
    
    void AddRule(IRule* r);
    void RemoveRule(IRule* r);
    IRule* GetRuleNamed(std::string name);

    void AddBoid(Boid* boid);
    void AddBoid(ISceneNode* node);
    
    void Handle(Core::ProcessEventArg arg);
    void ReloadProperties(Utils::PropertyTreeNode* n);
    TransformationNode* GetTransformationNode(int idx);
    void SetPropertyNode(Utils::PropertyTreeNode* n);
};

} // NS Animations
} // NS OpenEngine

#endif // _OE_FLOCK_H_
