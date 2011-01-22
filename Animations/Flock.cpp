#include "Flock.h"

#include <Scene/SceneNode.h>

namespace OpenEngine {
namespace Animations {

using namespace std;
using namespace Math;

Flock::Flock() : rootNode(new SceneNode())
               , randomGenerator(new RandomGenerator()) {    
}

ISceneNode* Flock::GetRootNode() {
    return rootNode;
}

void Flock::AddBoid(Boid* boid) {
    boids.push_back(boid);
    rootNode->AddNode(boid->GetTransformationNode());
}

void Flock::AddBoid(ISceneNode* node) {
    Boid* b = new Boid(node,randomGenerator);
    boids.push_back(b);
    rootNode->AddNode(b->GetTransformationNode());
}

TransformationNode* Flock::GetTransformationNode(int idx) {
    Boid* b = boids.at(idx);
    return b->GetTransformationNode();
}


void Flock::AddRule(IRule* r) {
    rules.push_back(r);
}

void Flock::RemoveRule(IRule* r) {
    rules.remove(r);
}


void Flock::ReloadProperties(Utils::PropertyTreeNode n) {
    for (list<IRule*>::iterator itr = rules.begin();
         itr != rules.end();
         itr++) {
        IRule *rule = *itr;
        rule->ReloadProperties(n);
    }    
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
