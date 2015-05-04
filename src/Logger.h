//
//  Logger.h
//  airsketcher
//
//  Created by Kevin Wong on 3/20/15.
//
//

#ifndef __airsketcher__Logger__
#define __airsketcher__Logger__

#include "ofMain.h"

#include "ofxXmlSettings.h"

class Logger
{
public:
    
    static const int maxNumLog = 25;
    
    static Logger* getInstance();
    
    void temporaryLog(std::string message);
    void logToFile(std::string mode, float startTime, float endTime, float interval);
    void log(std::string message);
    void print();
    
    void nextTask();
    bool getIsSystemGrab();
    
    std::string getTempMessage();
    
//    void playErrorSound();
//    void playStartModeSound();
//    void playEndModeSound();
    
private:
    Logger();
    ~Logger();
    
    std::deque<std::string> messages;
    
    float time;
    std::string temporaryMessage;
    
    static Logger* singleton;
    
    ofFile          logFile;
    ofxXmlSettings  settings;
    
    int user;
    int task1;
    int task2;
    int task3;
    int system;
    
    int current_task;
};


#endif /* defined(__airsketcher__Logger__) */
