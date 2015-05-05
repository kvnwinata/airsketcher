//
//  GrabCylinderCreatingMode.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 5/1/15.
//
//

#include "GrabCylinderCreatingMode.h"

#include "AirCommandCylinder.h"
#include "AirCylinder.h"
#include "Logger.h"

#define DEFAULT_HEIGHT  20
#define DEFAULT_RADIUS  10

std::vector<std::string> GrabCylinderCreatingMode::getCommands()
{
    std::vector<std::string> commands;
    commands.push_back("computer draw cylinder");
    commands.push_back("computer cancel");
    return commands;
}

GrabCylinderCreatingMode::GrabCylinderCreatingMode()
: AirControlMode()
, drawCylinderMode(NONE)
, newCylinder(NULL)
{
    circleTraces.resize(2, ofPoint());
}

GrabCylinderCreatingMode::~GrabCylinderCreatingMode()
{
    
}

void GrabCylinderCreatingMode::drawMode()
{
    if (drawCylinderMode == DRAW) {
        for (auto it = circleTraces.begin(); it != circleTraces.end(); )
        {
            const ofPoint& p1 = *it;
            it++;
            if (it != circleTraces.end())
            {
                const ofPoint& p2 = *it;
                ofLine(p1, p2);
            }
        }
    }
}

bool GrabCylinderCreatingMode::tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == "draw cylinder")
    {
        hasCompleted = false;
        startTime = ofGetElapsedTimeMillis();
        return true;
    }
    hasCompleted = true;
    return false;
}

void GrabCylinderCreatingMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    std::string command = speechProcessor.getLastCommand();
    bool isCancelled = false;
    bool lost = false;

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
                switch (drawCylinderMode) {
                    case DRAW:
                    {
                        circleTraces[1] = hand->getTipLocation();
                        float radius = computeBaseCircleTraceRadius(newCylinder->getPosition());
                        newCylinder->setRadius(radius);
                        
                        float height = hand->getTipLocation()[2] - cylinderBaseLoc[2];
                        ofPoint centroid = computeCylinderCentroid(height);
                        newCylinder->setPosition(centroid);
                        newCylinder->setHeight(abs(height));
                        break;
                    }
                    case NONE:
                    {
                        circleTraces[0] = hand->getTipLocation() - ofPoint(DEFAULT_RADIUS, DEFAULT_RADIUS, DEFAULT_RADIUS);
                        circleTraces[1] = hand->getTipLocation() + ofPoint(DEFAULT_RADIUS, DEFAULT_RADIUS, DEFAULT_RADIUS);
                        if (!createCylinder(controller, objectManager))
                        {
                            Logger::getInstance()->temporaryLog("FAILED to create new CYLINDER");
                            hasCompleted = true;
                        }
                        drawCylinderMode = DRAW;
                        break;
                    }
                    default:
                        break;
                }
            }
            else if (drawCylinderMode == DRAW)
            {
                drawCylinderMode = DONE;
                std::stringstream msg;
                msg << "Created CYLINDER (FINAL) with RADIUS ";
                msg << newCylinder->getRadius();
                msg << " and HEIGHT ";
                msg << newCylinder->getHeight();
                Logger::getInstance()->temporaryLog(msg.str());
                hasCompleted = true;
            }
        }
        else
        {
            // hand is lost
            hasCompleted = true;
            lost = true;
        }
    }
    
    if (hasCompleted)
    {
        if (isCancelled) {
            if (NULL != newCylinder) {
                controller->popCommand();                
            }
        }
        newCylinder = NULL;
        drawCylinderMode = NONE;
        circleTraces.resize(2, ofPoint());
        Logger::getInstance()->logToFile(isCancelled ? cancelTag : (lost ? lostTag : completeTag), startTime, ofGetElapsedTimeMillis());
    }
}

bool GrabCylinderCreatingMode::createCylinder(AirController* controller, AirObjectManager &objectManager)
{
    cylinderBaseLoc = computeBaseCircleTraceCentroid();
    float radius = computeBaseCircleTraceRadius(cylinderBaseLoc);
    if (radius > 0)
    {
        float height =  DEFAULT_HEIGHT;
        ofPoint centroid = computeCylinderCentroid(height);
        
        AirCommandCylinder* cmd = new AirCommandCylinder(objectManager, centroid, radius, height);
        if (!controller->pushCommand(cmd))
        {
            return false;
        }
        newCylinder = dynamic_cast<AirCylinder*>(cmd->getObject());
        
        std::stringstream msg;
        msg << "Created CYLINDER (INITIAL) with RADIUS ";
        msg << radius;
        msg << " and HEIGHT ";
        msg << height;
        Logger::getInstance()->temporaryLog(msg.str());
        return true;
    }
    return false;
}

std::string GrabCylinderCreatingMode::getStatusMessage()
{
    switch (drawCylinderMode) {
        case DRAW:
        {
            std::stringstream msg;
            msg << "Drawing CYLINDER: current radius ";
            msg << newCylinder->getRadius();
            return msg.str();
        }
        case DONE:
            return "Drawing CYLINDER: done";
        default:
            return "Drawing CYLINDER: do nothing";
    }
}

std::string GrabCylinderCreatingMode::getHelpMessage()
{
    std::string msg;
    switch (drawCylinderMode) {
        case NONE:
            msg = "Pinch your hand and move around to draw and adjust the radius and height. \n";
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
