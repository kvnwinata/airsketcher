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

class Logger
{
public:
    
    static const int maxNumLog = 25;
    
    static Logger* getInstance();
    
    void temporaryLog(std::string message);
    void log(std::string message);
    void print();
    
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
    
};


#endif /* defined(__airsketcher__Logger__) */
