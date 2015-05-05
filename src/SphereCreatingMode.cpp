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

#define DEFAULT_RADIUS  20

std::vector<std::string> SphereCreatingMode::getCommands()
{
    std::vector<std::string> commands;
    commands.push_back("computer draw sphere");
    commands.push_back("computer place");
    commands.push_back("computer done");
    commands.push_back("computer cancel");
    return commands;
}

SphereCreatingMode::SphereCreatingMode()
    : AirControlMode()
    , sphere(NULL)
{
    traces.resize(2, ofPoint());
}

SphereCreatingMode::~SphereCreatingMode()
{
    
}

void SphereCreatingMode::drawMode()
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

bool SphereCreatingMode::tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == "draw sphere")
    {
        LeapHand* hand = handProcessor.getHandAtIndex(0);
        traces[0] = hand->getTipLocation() - ofPoint(DEFAULT_RADIUS, DEFAULT_RADIUS, DEFAULT_RADIUS);
        traces[1] = hand->getTipLocation() + ofPoint(DEFAULT_RADIUS, DEFAULT_RADIUS, DEFAULT_RADIUS);
        if (!createSphere(controller, objectManager))
        {
            Logger::getInstance()->temporaryLog("Drawing sphere FAILED; cannot allocate new copy");
            hasCompleted = true;
            return false;
        }
        hasCompleted = false;
        startTime = ofGetElapsedTimeMillis();
        return true;
    }
    hasCompleted = true;
    return false;
}

void SphereCreatingMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    std::string command = speechProcessor.getLastCommand();
    bool isCancelled = false;

    if (command == "place" || command == "done")
    {
        hasCompleted = true;
    }
    else if (command == "cancel")
    {
        isCancelled = true;
        hasCompleted = true;
    } 
    else 
    {
        LeapHand* hand = handProcessor.getHandAtIndex(0);
        
        if (hand->getIsActive())
        {
            traces[1] = hand->getTipLocation();
            float radius = computeTraceRadius(sphere->getPosition());
            sphere->setRadius(radius);
        }
        else
        {
            // hand is lost
            hasCompleted = true;
        }
    }

    if (hasCompleted)
    {
        if (isCancelled) {
            if (NULL != sphere) {
                controller->popCommand();                
            }
            Logger::getInstance()->logToFile("voice-sphere-canceled", startTime, ofGetElapsedTimeMillis());
        } else {
            Logger::getInstance()->logToFile("voice-sphere", startTime, ofGetElapsedTimeMillis());
        }
        sphere = NULL;
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
        sphere = cmd->getObject();
        return true;
    }
    return false;
}

std::string SphereCreatingMode::getStatusMessage()
{
    if (NULL != sphere) {
        std::stringstream msg;
        msg << "Drawing SPHERE ";
        msg << sphere->getDescription();
        msg << "\n at ";
        msg << sphere->getPosition();
        msg << "\n with radius ";
        msg << sphere->getRadius();
    }
    return "Drawing SPHERE: do nothing";
}

std::string SphereCreatingMode::getHelpMessage()
{
    std::string msg =
        "Move outwards or inwards to resize.\n"
        "When finished, say 'computer cancel'\n"
        "OR to cancel midway, say 'computer cancel'\n";
    return msg;
}
