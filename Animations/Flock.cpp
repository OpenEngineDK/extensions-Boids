#include "Flock.h"

#include <Scene/SceneNode.h>

namespace OpenEngine {
namespace Animations {

    Flock::Flock() : rootNode(new SceneNode()) {
}

    ISceneNode* Flock::GetRootNode() {
        return rootNode;
    }
    void Flock::AddBoid(ISceneNode* node) {
        Boid *b = new Boid(node);
        boids.push_back(b);
        rootNode->AddNode(b->GetTransformationNode());
    }
    void Flock::Handle(Core::ProcessEventArg arg) {
}


}
}
