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
#include <string>
#include <Utils/PropertyTree.h>
#include <Utils/PropertyTreeNode.h>
#include <Core/IListener.h>
#include <algorithm>
#include <string> 

namespace OpenEngine {
namespace Animations {

using Utils::PropertiesChangedEventArg;

/**
 * Short description.
 *
 * @class IRule IRule.h ons/Boids/Animations/IRule.h
 */
class IRule : public Core::IListener<PropertiesChangedEventArg> {
private:
    std::string name;

public:
    IRule(std::string name) : name(name) {}
    std::string GetName() { return name; }
    virtual void UpdateBoids(std::vector<Boid*> boids) =0;
    virtual void ReloadProperties(Utils::PropertyTreeNode* pn) =0;
    void SetPropertyNode(Utils::PropertyTreeNode* node) {
        std::string data = GetName();
        std::transform(data.begin(), data.end(), data.begin(), ::tolower);
        Utils::PropertyTreeNode* n = node->GetNode(data);

        n->PropertiesChangedEvent().Attach(*this);
    }

    void Handle(Utils::PropertiesChangedEventArg arg) {
        // Legacy, we except to get the parent
        ReloadProperties(arg.GetNode()->GetParent());
    }
};
} // NS Animations
} // NS OpenEngine

#endif // _OE_I_RULE_H_
