//
//  AirController.h
//  airsketcher
//
//  Created by Kevin Wong on 3/20/15.
//  Last update by Patricia Suriana on 4/14/15
//
//

#ifndef __airsketcher__AirController__
#define __airsketcher__AirController__

#include "ofMain.h"

#include "AirCommand.h"
#include "AirController.h"
#include "AirObjectManager.h"
#include "HandProcessor.h"
#include "SpeechProcessor.h"

class AirControlMode;

class AirController
{
public:
    
    AirController();
    ~AirController();
    
    void draw();
    void update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager);
    
    std::vector<std::string> getCommands();
    
    std::string getStatusMessage();
    std::string getHelpMessage();
    
    // Push the command on the top of the undoCommands stack and call execute cmd
    // This method takes ownership of cmd
    bool pushCommand(AirCommand* cmd);
    
    // Call unexecute on cmd at the top of the undoCommands stack and pop that command
    void popCommand();
    
    void undoCommands(int levels);
    void redoCommands(int levels);
    
private:
    
    AirControlMode* currentMode;
    
    std::vector<AirControlMode*> modes;
    
    // For undo-redo
    std::vector<AirCommand*> undoStack;
    std::vector<AirCommand*> redoStack;
};


class AirControlMode
{
public:
    
    AirControlMode() : hasCompleted(true), startTime(0) {}
    virtual ~AirControlMode() {}
    
    virtual bool tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) = 0;
    virtual void update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) = 0;
    virtual void drawMode() = 0;
    virtual std::vector<std::string> getCommands() = 0;
    
    bool getHasCompleted() const { return hasCompleted; }
    
    virtual std::string getStatusMessage() = 0;
    virtual std::string getHelpMessage() { return "Help message not implemented for this mode!"; }
    
protected:
    bool hasCompleted;
    float startTime;
};

#endif /* defined(__airsketcher__AirController__) */
