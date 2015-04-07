//
//  SphereCreatingMode.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 3/31/15.
//
//

#include "SphereCreatingMode.h"

#include "AirSphere.h"
#include "Logger.h"

std::vector<std::string> SphereCreatingMode::getCommands()
{
    std::vector<std::string> commands;
    commands.push_back("computer draw sphere");
    commands.push_back("computer cancel");
    return commands;
}

SphereCreatingMode::SphereCreatingMode()
    : AirControlMode()
    , drawCircleMode(NONE)
{
    
}

SphereCreatingMode::~SphereCreatingMode()
{
    
}

void SphereCreatingMode::drawMode()
{
    if (drawCircleMode == DRAW)
    {
        for (auto it = traces.begin(); it != traces.end(); )
        {
            const ofPoint& p1 = *it;
            it++;
            if (it != traces.end())
            {
                const ofPoint& p2 = *it;
                ofLine(p1, p2);
            }
        }
    }
}

bool SphereCreatingMode::tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == "draw sphere")
    {
        hasCompleted = false;
        return true;
    }
    return false;
}

void SphereCreatingMode::update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    std::string command = speechProcessor.getLastCommand();
    if (command == "cancel")
    {
        hasCompleted = true;
    } 
    else 
    {
        LeapHand* hand = handProcessor.getHandAtIndex(0);
        
        if (hand->getIsActive())
        {
            if (hand->getIsPinching())
            {
                switch (drawCircleMode) {
                    case DRAW:
                        traces.push_back(hand->getTipLocation());
                        break;
                    case NONE:
                        drawCircleMode = DRAW;
                        break;
                    default:
                        break;
                }
            }
            else if (drawCircleMode == DRAW)
            {
                drawCircleMode = DONE;
                hasCompleted = true;
            }
        }
        else
        {
            // hand is lost
            hasCompleted = true;
        }
        
        if (drawCircleMode == DONE) {
            if (!createSphere(objectManager))
            {
                std::stringstream msg;
                msg << "FAILED to create new SPHERE; trace size ";
                msg << traces.size();
                Logger::getInstance()->temporaryLog(msg.str());
            }
        }
    }

    if (hasCompleted)
    {
        drawCircleMode = NONE;
        traces.clear();
    }
}

bool SphereCreatingMode::createSphere(AirObjectManager &objectManager)
{
    ofPoint centroid = computeTraceCentroid();
    float radius = computeTraceRadius(centroid);
    if (radius > 0.0) {
        AirSphere* sphere = new AirSphere();
        sphere->setup(centroid, radius, ofColor::gray); // Default color: gray
        objectManager.addObject(sphere);
        return true;
    }
    return false;
}

std::string SphereCreatingMode::getStatusMessage()
{
    switch (drawCircleMode) {
        case DRAW:
        {
            std::stringstream msg;
            msg << "DRAWING SPHERE: current trace size ";
            msg << traces.size();
            return msg.str();
        }
        case DONE:
            return "DRAWING SPHERE: DONE";
        default:
            return "DRAWING SPHERE: do nothing";
    }
}