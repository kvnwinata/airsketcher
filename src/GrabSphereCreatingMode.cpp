//
//  GrabSphereCreatingMode.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 5/1/15.
//
//

#include "GrabSphereCreatingMode.h"

#include "AirCommandSphere.h"
#include "AirSphere.h"
#include "Logger.h"

#define DEFAULT_RADIUS  20

std::vector<std::string> GrabSphereCreatingMode::getCommands()
{
    std::vector<std::string> commands;
    commands.push_back("computer draw sphere");
    commands.push_back("computer cancel");
    return commands;
}

GrabSphereCreatingMode::GrabSphereCreatingMode()
: AirControlMode()
, drawCircleMode(NONE)
, sphere(NULL)
{
    traces.resize(2, ofPoint());
}

GrabSphereCreatingMode::~GrabSphereCreatingMode()
{
    
}

void GrabSphereCreatingMode::drawMode()
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

bool GrabSphereCreatingMode::tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == "draw sphere")
    {
        hasCompleted = false;
        startTime = ofGetElapsedTimeMillis();
        return true;
    }
    hasCompleted = true;
    return false;
}

void GrabSphereCreatingMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
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
                    {
                        traces[1] = hand->getTipLocation();
                        float radius = computeTraceRadius(sphere->getPosition());
                        sphere->setRadius(radius);
                        break;
                    }
                    case NONE:
                        traces[0] = hand->getTipLocation() - ofPoint(DEFAULT_RADIUS, DEFAULT_RADIUS, DEFAULT_RADIUS);
                        traces[1] = hand->getTipLocation() + ofPoint(DEFAULT_RADIUS, DEFAULT_RADIUS, DEFAULT_RADIUS);
                        if (!createSphere(controller, objectManager))
                        {
                            Logger::getInstance()->temporaryLog("Drawing sphere FAILED; cannot allocate new copy");
                            hasCompleted = true;
                        }
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
    }
    
    if (hasCompleted)
    {
        if (isCancelled) {
            if (NULL != sphere) {
                controller->popCommand();                
            }
            Logger::getInstance()->logToFile("grab-sphere-canceled", startTime, ofGetElapsedTimeMillis());
        } else {
            Logger::getInstance()->logToFile("grab-sphere", startTime, ofGetElapsedTimeMillis());
        }
        sphere = NULL;
        drawCircleMode = NONE;
        traces.resize(2, ofPoint());
    }
}

bool GrabSphereCreatingMode::createSphere(AirController* controller, AirObjectManager &objectManager)
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

std::string GrabSphereCreatingMode::getStatusMessage()
{
    switch (drawCircleMode) {
        case DRAW:
        {
            std::stringstream msg;
            msg << "Drawing SPHERE ";
            msg << sphere->getDescription();
            msg << "\n at ";
            msg << sphere->getPosition();
            msg << "\n with radius ";
            msg << sphere->getRadius();
        }
        case DONE:
            return "Drawing SPHERE: done";
        default:
            return "Drawing SPHERE: do nothing";
    }
}

std::string GrabSphereCreatingMode::getHelpMessage()
{
    std::string msg;
    switch (drawCircleMode){
        case NONE:
            msg = "Pinch your hand and move around (outwards or inwards) to draw and resize sphere. \n";
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