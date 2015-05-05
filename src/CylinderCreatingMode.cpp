//
//  CylinderCreatingMode.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 3/31/15.
//
//

#include "CylinderCreatingMode.h"

#include "AirCommandCylinder.h"
#include "AirCylinder.h"
#include "Logger.h"

#define DEFAULT_HEIGHT  20
#define DEFAULT_RADIUS  10

std::vector<std::string> CylinderCreatingMode::getCommands()
{
    std::vector<std::string> commands;
    commands.push_back("computer draw cylinder");
    commands.push_back("computer place");
    commands.push_back("computer done");
    commands.push_back("computer cancel");
    return commands;
}

CylinderCreatingMode::CylinderCreatingMode()
    : AirControlMode()
    , newCylinder(NULL)
{
    circleTraces.resize(2, ofPoint());
}

CylinderCreatingMode::~CylinderCreatingMode()
{
    
}

void CylinderCreatingMode::drawMode()
{
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

bool CylinderCreatingMode::tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == "draw cylinder")
    {
        LeapHand* hand = handProcessor.getHandAtIndex(0);
        circleTraces[0] = hand->getTipLocation() - ofPoint(DEFAULT_RADIUS, DEFAULT_RADIUS, DEFAULT_RADIUS);
        circleTraces[1] = hand->getTipLocation() + ofPoint(DEFAULT_RADIUS, DEFAULT_RADIUS, DEFAULT_RADIUS);
        if (!createCylinder(controller, objectManager))
        {
            Logger::getInstance()->temporaryLog("FAILED to create new CYLINDER");
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

void CylinderCreatingMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    std::string command = speechProcessor.getLastCommand();
    bool isCancelled = false;
    bool lost = false;
    
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
            circleTraces[1] = hand->getTipLocation();
            float radius = computeBaseCircleTraceRadius(newCylinder->getPosition());
            newCylinder->setRadius(radius);
            
            float height = hand->getTipLocation()[2] - cylinderBaseLoc[2];
            ofPoint centroid = computeCylinderCentroid(height);
            newCylinder->setPosition(centroid);
            newCylinder->setHeight(abs(height));
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
        circleTraces.resize(2, ofPoint());
        Logger::getInstance()->logToFile(isCancelled ? cancelTag : (lost ? lostTag : completeTag), startTime, ofGetElapsedTimeMillis());
    }
}

bool CylinderCreatingMode::createCylinder(AirController* controller, AirObjectManager &objectManager)
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

std::string CylinderCreatingMode::getStatusMessage()
{
    if (NULL != newCylinder) {
        std::stringstream msg;
        msg << "Drawing CYLINDER: current radius: ";
        msg << newCylinder->getRadius();
        msg << "; height: ";
        msg << newCylinder->getHeight();
        return msg.str();
    }
    return "Drawing CYLINDER: do nothing";
}

std::string CylinderCreatingMode::getHelpMessage()
{
    std::string msg =
    "Move outwards or inwards to resize.\n"
    "When finished, say 'computer cancel'\n"
    "OR to cancel midway, say 'computer cancel'\n";
    return msg;
}
