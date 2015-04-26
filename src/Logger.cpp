//
//  Logger.cpp
//  airsketcher
//
//  Created by Kevin Wong on 3/20/15.
//
//

#include "Logger.h"

Logger* Logger::singleton = NULL;

Logger* Logger::getInstance()
{
    if (singleton == 0)
    {
        singleton = new Logger();
    }
    return singleton;
}

void Logger::log(std::string message)
{
    messages.push_front(message);
    
    if (messages.size() > maxNumLog)
    {
        messages.pop_back();
    }
}

void Logger::temporaryLog(std::string message)
{
    temporaryMessage = message;
    time = ofGetElapsedTimef();
}

void Logger::print()
{
    ofSetColor(255,255,255);
    ofPushMatrix();
    
    if (ofGetElapsedTimef() - time < 8)
    {
        ofDrawBitmapString(temporaryMessage, ofPoint(0,0));
    }

    for (std::string message : messages)
    {
        ofTranslate(0, 15);
        ofDrawBitmapString(message, ofPoint(0,0));
    }
    
    ofPopMatrix();
}

//void Logger::playStartModeSound(){startModeSound.play();}
//void Logger::playEndModeSound(){endModeSound.play();}
//void Logger::playErrorSound(){errorSound.play();}

Logger::Logger() : temporaryMessage("")
{

}

Logger::~Logger(){}