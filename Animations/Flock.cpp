#include "Flock.h"

#include <Scene/SceneNode.h>

namespace OpenEngine {
namespace Animations {

    using namespace std;

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

void Flock::AddRule(IRule* r) {
    rules.push_back(r);
}

void Flock::Handle(Core::ProcessEventArg arg) {
    // Fire rules
    for (list<IRule*>::iterator itr = rules.begin();
         itr != rules.end();
         itr++) {
        IRule *rule = *itr;
        rule->UpdateBoids(boids);
    }
    
    // Update positions
    for (vector<Boid*>::iterator itr = boids.begin();
         itr != boids.end();
         itr++) {
        Boid *b = *itr;
        b->Update(arg.approx);
    }
}
    

}
}
