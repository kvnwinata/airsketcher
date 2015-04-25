//
//  SphereCreatingMode.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 3/31/15.
//
//

#include "SphereCreatingMode.h"

#include "AirCommandSphere.h"
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
    traces.resize(2, ofPoint());
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

bool SphereCreatingMode::tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == "draw sphere")
    {
        hasCompleted = false;
        return true;
    }
    return false;
}

void SphereCreatingMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    std::string command = speechProcessor.getLastCommand();
    bool isCancelled = false;

    if (command == "cancel")
    {
        isCancelled = true;
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
                        traces[1] = hand->getTipLocation();
                        break;
                    case NONE:
                        traces[0] = hand->getTipLocation();
                        traces[1] = hand->getTipLocation();
                        drawCircleMode = DRAW;
                        break;
                    default:
                        break;
                }
            }
            else if (drawCircleMode == DRAW)
            {
                drawCircleMode = DONE;
            }
        }
        else
        {
            // hand is lost
            hasCompleted = true;
        }
        
        if (drawCircleMode == DONE) {
            if (!createSphere(controller, objectManager))
            {
                std::stringstream msg;
                msg << "FAILED to create new SPHERE; trace size ";
                msg << traces.size();
                Logger::getInstance()->temporaryLog(msg.str());
            }
            hasCompleted = true;
        }
    }

    if (hasCompleted)
    {
        if (isCancelled) {
            controller->popCommand();
        }
        drawCircleMode = NONE;
        traces.resize(2, ofPoint());
    }
}

bool SphereCreatingMode::createSphere(AirController* controller, AirObjectManager &objectManager)
{
    ofPoint centroid = computeTraceCentroid();
    float radius = computeTraceRadius(centroid);
    if (radius > 0.0)
    {
        AirCommandSphere* cmd = new AirCommandSphere(objectManager, centroid, radius);
        if (!controller->pushCommand(cmd))
        {
            return false;
        }
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
            msg << "DRAWING SPHERE";
            return msg.str();
        }
        case DONE:
            return "DRAWING SPHERE: DONE";
        default:
            return "DRAWING SPHERE: do nothing";
    }
}

std::string SphereCreatingMode::getHelpMessage()
{
    std::string msg;
    switch (drawCircleMode){
        case NONE:
            msg = "Pinch your fingers and draw line (radius + centroid). \n";
            break;
        case DRAW:
            msg = "When finished, release your pinch\n OR to cancel midway, say 'computer cancel'\n";
            break;
        case DONE:
            msg = "You're done!";
            break;
    }
    return msg;
}
