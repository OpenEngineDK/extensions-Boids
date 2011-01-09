#include "Boid.h"

namespace OpenEngine {
namespace Animations {


    Boid::Boid(ISceneNode* node) {
        transformationNode = new TransformationNode();
        transformationNode->AddNode(node);
    }

    TransformationNode* Boid::GetTransformationNode() {
        return transformationNode;
    }

    

}
}
