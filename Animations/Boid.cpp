#include "Boid.h"

#include <Logging/Logger.h>

namespace OpenEngine {
namespace Animations {
    
using namespace Math;

Boid::Boid(ISceneNode* node, RandomGenerator* rg) {
    transformationNode = new TransformationNode();
    transformationNode->AddNode(node);
    position = Vector<3,float>(rg->UniformFloat(-40,40),
                               rg->UniformFloat(-40,40),
                               rg->UniformFloat(-40,40));
    transformationNode->SetPosition(position);
    velocity = Vector<3,float>(0,0,0);
}

TransformationNode* Boid::GetTransformationNode() {
    return transformationNode;
}

Vector<3,float> Boid::GetPosition() const {
    return position;
}

void Boid::SetPosition(Vector<3,float> p) {
    position = p;
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
    
    rotation = Quaternion<float>(rotation,newRot.GetNormalize(),10*delta); // Rotate 10%
    //rotation = Quaternion<float>(rotation,newRot.GetNormalize(),0.1); // Rotate 10%
    //rotation = newRot;
    transformationNode->SetRotation(rotation);

    prev = velocity;
    
}

}
}
