// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------


#ifndef _OE_FLOCK_PROPERTY_RELOADER_H_
#define _OE_FLOCK_PROPERTY_RELOADER_H_

#include <Core/IListener.h>
#include <Utils/PropertyTree.h>
#include <Animations/Flock.h>
#include <Core/IListener.h>
#include <Logging/Logger.h>
#include <string>


namespace OpenEngine {
namespace Animations {

using OpenEngine::Core::IListener;
using namespace OpenEngine::Utils;

/**
 * Short description.
 *
 * @class FlockPropertyReloader FlockPropertyReloader.h ons/Boids/Animations/FlockPropertyReloader.h
 */
class FlockPropertyReloader  : public Core::IListener<Utils::PropertiesChangedEventArg>
{
private:
    Flock* flock;
    Utils::PropertyTree *ptree;
    std::string keyPath;
public:
    FlockPropertyReloader(Flock* f, Utils::PropertyTree* pt, std::string kp) 
        : flock(f)
        , ptree(pt)
        , keyPath(kp) {
        ptree->PropertiesChangedEvent().Attach(*this);
    }

    void Handle(Utils::PropertiesChangedEventArg arg) {
        flock->ReloadProperties(ptree->GetRootNode()->GetNode(keyPath));
        logger.info << "Reloading" << logger.end;
    }
};
} // NS Animations
} // NS OpenEngine

#endif // _OE_FLOCK_PROPERTY_RELOADER_H_
