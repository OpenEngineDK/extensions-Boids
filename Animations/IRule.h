// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------


#ifndef _OE_I_RULE_H_
#define _OE_I_RULE_H_

#include <vector>
#include <Utils/PropertyTree.h>

namespace OpenEngine {
namespace Animations {

/**
 * Short description.
 *
 * @class IRule IRule.h ons/Boids/Animations/IRule.h
 */
class IRule {
public:
    virtual void UpdateBoids(std::vector<Boid*> boids) =0;
    virtual void ReloadProperties(Utils::PropertyTreeNode pn) {}
};
} // NS Animations
} // NS OpenEngine

#endif // _OE_I_RULE_H_
