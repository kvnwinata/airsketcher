//
//  BoxCreatingMode.cpp
//  airsketcher
//
//  Created by Pramod Kandel on 5/4/15.
//
//

#include "BoxCreatingMode.h"

#include "AirCommandBox.h"
#include "logger.h"

#define DEFAULT_LENGTH 20

std::vector<std::string> BoxCreatingMode::getCommands()
{
    std::vector<std::string> commands;
    commands.push_back("computer "+drawCommand);
    commands.push_back("computer done");
    commands.push_back("computer cancel");
    return commands;
}

BoxCreatingMode::BoxCreatingMode() : AirControlMode(), box(NULL)
{
    traces.resize(2, ofPoint());
}

BoxCreatingMode::~BoxCreatingMode()
{
    
}

void BoxCreatingMode::drawMode()
{
    ofLine(getStartPoint(), getEndPoint());
    
}

bool BoxCreatingMode::tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == drawCommand)
    {
        LeapHand* hand = handProcessor.getHandAtIndex(0);
        traces[0] = hand->getTipLocation() - ofPoint(DEFAULT_LENGTH, DEFAULT_LENGTH, DEFAULT_LENGTH);
        traces[1] = hand->getTipLocation() + ofPoint(DEFAULT_LENGTH, DEFAULT_LENGTH, DEFAULT_LENGTH);
        if (!createBox(controller, objectManager))
        {
            Logger::getInstance()->temporaryLog("Drawing box FAILED; cannot allocate new copy");
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

void BoxCreatingMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    std::string command = speechProcessor.getLastCommand();
    bool isCancelled = false;
    bool lost = false;
    
    if (command == "done")
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

            traces.push_back(hand->getTipLocation());
            ofVec3f size_xyz = getSize();
            box->setSize(size_xyz);
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
            if (NULL != box) {
                controller->popCommand();                
            }
        }
        box = NULL;
        traces.resize(2, ofPoint());
        Logger::getInstance()->logToFile(isCancelled ? cancelTag : (lost ? lostTag : completeTag), startTime, ofGetElapsedTimeMillis());
    }
}


bool BoxCreatingMode::createBox(AirController* controller, AirObjectManager &objectManager)
{
    ofVec3f size_xyz = getSize();
    ofPoint center = getCenterPosition();
    float dist = size_xyz.length();
    
    if (dist != 0.0)
    {
        AirCommandBox* cmd = new AirCommandBox(objectManager, center, size_xyz);
        if (!controller->pushCommand(cmd))
        {
            return false;
        }
        box = cmd-> getObject();
        return true;
    }
    
    return false;
}


std::string BoxCreatingMode::getStatusMessage()
{
    if (NULL != box)
    {
        std::stringstream msg;
        msg << "Drawing SPHERE ";
        msg << box->getDescription();
        msg << "\n at ";
        msg << box->getPosition();
    }
    return "Drawing BOX..";
}


std::string BoxCreatingMode::getHelpMessage()
{
    std::string msg =
    "Move outwards or inwards to resize.\n"
    "When finished, say 'computer done'\n"
    "OR to cancel midway, say 'computer cancel'\n";
    return msg;
}

