//
//  GrabBoxCreatingMode.cpp
//  airsketcher
//
//  Created by Pramod Kandel on 4/6/15.
//  Last update by Patricia Suriana on 4/14/15.
//
//

#include "GrabBoxCreatingMode.h"

#include "AirCommandBox.h"
#include "logger.h"

#define DEFAULT_LENGTH 20

std::vector<std::string> GrabBoxCreatingMode::getCommands()
{
    std::vector<std::string> commands;
    commands.push_back("computer "+drawCommand);
    return commands;
}

GrabBoxCreatingMode::GrabBoxCreatingMode() : AirControlMode(), box(NULL), drawBoxMode(NONE)
{
    traces.resize(2, ofPoint());
}

GrabBoxCreatingMode::~GrabBoxCreatingMode()
{
    
}

void GrabBoxCreatingMode::drawMode()
{
    if (drawBoxMode == DRAW)
    {
        ofLine(getStartPoint(), getEndPoint());
        
    }
    
}

bool GrabBoxCreatingMode::tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == drawCommand)
    {
        hasCompleted = false;
        startTime = ofGetElapsedTimeMillis();
        return true;
    }
    hasCompleted = true;
    return false;
}

void GrabBoxCreatingMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
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
                switch (drawBoxMode) {
                    case DRAW:
                    {
                        traces.push_back(hand->getTipLocation());
                        ofVec3f size_xyz = getSize();
                        box->setSize(size_xyz);
                        break;
                    }
                    case NONE:
                        traces[0] = hand->getTipLocation() - ofPoint(DEFAULT_LENGTH, DEFAULT_LENGTH, DEFAULT_LENGTH);
                        traces[1] = hand->getTipLocation() + ofPoint(DEFAULT_LENGTH, DEFAULT_LENGTH, DEFAULT_LENGTH);
                        if (!createBox(controller, objectManager))
                        {
                            Logger::getInstance()->temporaryLog("Drawing box FAILED; cannot allocate new copy");
                            hasCompleted = true;
                        }                        
                        drawBoxMode = DRAW;
                        break;
                    default:
                        break;
                }
            }
            else if (drawBoxMode == DRAW)
            {
                drawBoxMode = DONE;
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
            if (NULL != box) {
                controller->popCommand();                
            }
        }
        box = NULL;
        drawBoxMode = NONE;
        traces.resize(2, ofPoint());
        Logger::getInstance()->logToFile(isCancelled ? cancelTag : (lost ? lostTag : completeTag), startTime, ofGetElapsedTimeMillis());
    }
}


bool GrabBoxCreatingMode::createBox(AirController* controller, AirObjectManager &objectManager)
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


std::string GrabBoxCreatingMode::getStatusMessage()
{
    switch (drawBoxMode) {
        case DRAW:
        {
            return "BOX: Drawing";
        }
        case DONE:
            return "BOX: done";
            
        default:
            return "BOX: Pinch to draw.";
    }
}


std::string GrabBoxCreatingMode::getHelpMessage()
{
    std::string msg ="";
    switch (drawBoxMode){
        case DRAW:
            msg ="When finished, slowly release your pinch \n";
            break;
        case NONE:
            msg = "Pinch your all fingers together to start then pull your diagonal. \n";
            break;
        case DONE:
            msg = "You're done!";
            break;
    }
    return msg;
}
