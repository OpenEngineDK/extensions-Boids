#include "Boid.h"

#include <Math/RandomGenerator.h>
#include <Logging/Logger.h>

namespace OpenEngine {
namespace Animations {
    
using namespace Math;

Boid::Boid(ISceneNode* node) {
    transformationNode = new TransformationNode();
    transformationNode->AddNode(node);
    RandomGenerator rg;
    rg.SeedWithTime();
    position = Vector<3,float>(rg.UniformFloat(-20,20),
                               rg.UniformFloat(-20,20),
                               rg.UniformFloat(-20,20));
    transformationNode->SetPosition(position);
    velocity = Vector<3,float>(0,0,0);
}

TransformationNode* Boid::GetTransformationNode() {
    return transformationNode;
}

Vector<3,float> Boid::GetPosition() {
    return position;
}

Vector<3,float> Boid::GetVelocity() {
    return velocity;
}

    
void Boid::AddVelocity(Vector<3,float> v) {
    velocity += v;
}


void Boid::Update(unsigned int dt) {
    float delta = dt/1000000.0;

    position += velocity*delta;    
    transformationNode->SetPosition(position);
    if (velocity.GetLength() < 0.01)
        return;

    Vector<3,float> x = velocity.GetNormalize(); // x vector
    Vector<3,float> up(0,1,0); // up vector
    Vector<3,float> z = x % up;
    if (x.GetLength() < 0.01)
        return;
    Vector<3,float> y = z % x;

    Matrix<3,3,float> rotMat(x,y,z);
    Quaternion<float> newRot(rotMat);
    rotation = Quaternion<float>(rotation,newRot.GetNormalize(),0.1); // Rotate 10%
    transformationNode->SetRotation(rotation);

    prev = velocity;
    
}

}
}
