#include "Boid.h"

#include <Math/RandomGenerator.h>

namespace OpenEngine {
namespace Animations {
    
    using namespace Math;

    Boid::Boid(ISceneNode* node) {
        transformationNode = new TransformationNode();
        RandomGenerator rg;
        rg.SeedWithTime();
        transformationNode->Move(rg.UniformFloat(-20,20),
                                 rg.UniformFloat(-20,20),
                                 rg.UniformFloat(-20,20));
        transformationNode->AddNode(node);
    }

    TransformationNode* Boid::GetTransformationNode() {
        return transformationNode;
    }

    

}
}
