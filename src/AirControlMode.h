//
//  AirControlMode.h
//  airsketcher
//
//  Created by Kevin Wong on 3/22/15.
//  Last update by Patricia Suriana on 4/14/15
//
//

#ifndef __airsketcher__AirControlMode__
#define __airsketcher__AirControlMode__

#include <vector>

#include "HandProcessor.h"
#include "SpeechProcessor.h"
#include "AirCommand.h"
#include "AirObjectManager.h"

class AirControlMode
{
    
public:
    
    AirControlMode();
    virtual ~AirControlMode();
    
    virtual bool tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) = 0;
    virtual void update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) = 0;
    virtual void drawMode() = 0;
    virtual std::vector<std::string> getCommands() = 0;
    
    bool getHasCompleted() const;
    
    virtual std::string getStatusMessage() = 0;
    virtual std::string getHelpMessage();
    
protected:
    bool hasCompleted;

    // For undo-redo
    std::vector<AirCommand*> undoCommands;
    std::vector<AirCommand*> redoCommands;

    // Push the command on the top of the undoCommands stack and call execute
    // This method takes ownership of cmd
    bool pushCommand(AirCommand* cmd);

    // Pop the command on the top of the undoCommands stack and call unexecute
    void popCommand();
};

#endif /* defined(__airsketcher__AirControlMode__) */
