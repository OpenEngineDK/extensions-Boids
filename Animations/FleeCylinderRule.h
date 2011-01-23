// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#ifndef _FLEE_CYLINDER_RULE_H_
#define _FLEE_CYLINDER_RULE_H_

#include <Animations/FleeRule.h>
#include <Scene/TransformationNode.h>

namespace OpenEngine {
namespace Animations {

using namespace Scene;

/**
 * Short description.
 *
 * @class FleeCylinderRule FleeCylinderRule.h ons/Boids/Animations/FleeCylinderRule.h
 */
class FleeCylinderRule : public FleeRule {
private:
    Vector<3,float> ax0;
    Vector<3,float> ax1;
    float radius;
    float scareFactor;

    float PointCylinderDistance(Vector<3,float> p, 
                                Vector<3,float> cyAx0, 
                                Vector<3,float> cyAx1, 
                                float cyRad);

public:
    // Flee from cylinder.
    FleeCylinderRule(TransformationNode* fleeFromTrans, 
                     Vector<3,float> axisPoint0, 
                     Vector<3,float> axisPoint1, 
                     float radius = 10.0, 
                     float scare = 1.0) 
        : FleeRule(fleeFromTrans)
        , ax0(axisPoint0)
        , ax1(axisPoint1)
        , radius(radius)
        , scareFactor(scare){}


    ~FleeCylinderRule() {}


    void ReloadProperties(Utils::PropertyTreeNode* pn) {
        // radius = pn->GetPath("flee.radius", radius);
        // scareFactor = pn->GetPath("flee.scare", scareFactor);
    }

    void SetCylinder(Vector<3,float> axisPoint0, 
                     Vector<3,float> axisPoint1, 
                     float radius ){
        this->ax0 = axisPoint0;
        this->ax1 = axisPoint1;
        this->radius = radius;
    }

    void SetRadius(float radius) {
        this->radius = radius;
    }

    void UpdateBoids(std::vector<Boid*> boids) {

        Quaternion<float> r;
        Vector<3,float> enemyPos;
        Vector<3,float> s;
        fleeFromTrans->GetAccumulatedTransformations(&enemyPos,&r,&s);

        Vector<3,float> accAx0 = ax0 + (enemyPos);
        Vector<3,float> accAx1 = ax1 + (enemyPos);

        //logger.info << "RulePos: " << accAx0 << ", " << accAx1 << logger.end;


        float radiusSq = radius*radius;

        for (std::vector<Boid*>::iterator itr = boids.begin();
             itr != boids.end();
             itr++) {
        
            Boid* b = *itr;
            Vector<3,float> boidPos = b->GetPosition();

            // Get distance from boid to cylinder
            float distSq = PointCylinderDistance(boidPos, accAx0, accAx1, radiusSq);
            
            if( distSq > 0 && distSq < radiusSq ) {
            

                
                //Calculate shortest vector from cylinder axis to boid pos.
                Vector<3,float> axis = accAx1 - accAx0;
                Vector<3,float> w = boidPos - accAx0; 
                float cross0 = w * axis;
                float cross1 = axis * axis;
                float dist = cross0 / cross1;
                Vector<3,float> vecOnAxis = accAx0 + dist * axis;
                Vector<3,float> dir = (boidPos - vecOnAxis).GetNormalize();

                float withinCyl = sqrt(radiusSq - distSq);
                //logger.info << "radius " << radiusSq << ", dist " << distSq << ", distInside: " << withinCyl << logger.end;

                float danger = 1.0 - (distSq / radiusSq);
                Vector<3,float> fleeVec = dir * withinCyl * danger * scareFactor;
                //logger.info << "fleeVec: " << fleeVec << logger.end;
                b->AddVelocity(fleeVec);
            }
        }
    }
    
};


float FleeCylinderRule::PointCylinderDistance(Vector<3,float> p, 
                                              Vector<3,float> cyAx0, 
                                              Vector<3,float> cyAx1, 
                                              float cyRad) {

    // logger.info << "CyAx0: " << cyAx0 << ", " << cyAx1 << logger.end;


    //   p = Vector<3,float>(0, 50, -300);

    float length = (cyAx0 - cyAx1).GetLength();
    // square length
    float lengthSq = length * length;

    float dx, dy, dz;	    // vector d  from line segment point 1 to point 2
	float pdx, pdy, pdz;	// vector pd from point 1 to test point
	float dot, dsq;

	dx = cyAx1[0] - cyAx0[0];	    // translate so cyAx0 is origin.  Make vector from
	dy = cyAx1[1] - cyAx0[1];     // cyAx0 to cyAx1.  Need for this is easily eliminated
	dz = cyAx1[2] - cyAx0[2];

	pdx = p[0] - cyAx0[0];		// vector from cyAx0 to test point.
	pdy = p[1] - cyAx0[1];
	pdz = p[2] - cyAx0[2];

	// Dot the d and pd vectors to see if point lies behind the 
	// cylinder cap at cyAx0[0], cyAx0[1], cyAx0[2]

	dot = pdx * dx + pdy * dy + pdz * dz;
    // logger.info << "boidp: " << p << "dx,dy,dz: " << dx << ", " << dy << ", " << dz << ", dot: " << dot << logger.end;
    //logger.info << "pdx,y,z: " << pdx << ", " << pdy << ", " << pdz << logger.end;

	// If dot is less than zero the point is behind the cyAx0 cap.
	// If greater than the cylinder axis line segment length squared
	// then the point is outside the other end cap at cyAx1.

	if( dot < 0.0f || dot > lengthSq ){
		return( -1.0f );
	}
	else {
		// Point lies within the parallel caps, so find
		// distance squared from point to line, using the fact that sin^2 + cos^2 = 1
		// the dot = cos() * |d||pd|, and cross*cross = sin^2 * |d|^2 * |pd|^2
		// Carefull: '*' means mult for scalars and dotproduct for vectors
		// In short, where dist is pt distance to cyl axis: 
		// dist = sin( pd to d ) * |pd|
		// distsq = dsq = (1 - cos^2( pd to d)) * |pd|^2
		// dsq = ( 1 - (pd * d)^2 / (|pd|^2 * |d|^2) ) * |pd|^2
		// dsq = pd * pd - dot * dot / lengthsq
		//  where lengthsq is d*d or |d|^2 that is passed into this function 

		// distance squared to the cylinder axis:

		dsq = (pdx*pdx + pdy*pdy + pdz*pdz) - dot*dot/lengthSq;
        //        logger.info << "dist: " << sqrt(dsq) << logger.end;

		if( dsq > cyRad ){
			return( -1.0f );
		}
		else{
			return( dsq );		// return distance squared to axis
		}
	}
}


} // NS Animations
} // NS OpenEngine

#endif
