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

std::string Logger::getTempMessage()
{
    if (ofGetElapsedTimef() - time < 8)
    {
        return temporaryMessage;
    } else {
        return "";
    }
}

void Logger::print()
{
    ofSetColor(255,255,255);
    ofPushMatrix();
    
    if (ofGetElapsedTimef() - time < 8)
    {
        //ofDrawBitmapString(temporaryMessage, ofPoint(0,0));
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
    current_task = 0;
    settings.load("study.xml");
    
    user = settings.getValue("settings:user", 0);
    system = settings.getValue("settings:system", 0);
    task1 = settings.getValue("settings:task1", 0);
    task2 = settings.getValue("settings:task2", 0);
    task3 = settings.getValue("settings:task3", 0);
}

void Logger::nextTask()
{
    if (current_task > 0)
    {
        logFile.close();
    }
    
    current_task++;
    
    if (current_task > 4)
    {
        current_task = 4;
        return;
    }
    
    std::string timestamp =
    ofToString(ofGetMonth())    + "_" +
    ofToString(ofGetDay())      + "_" +
    ofToString(ofGetYear())     + "_" +
    ofToString(ofGetHours())    + "_" +
    ofToString(ofGetMinutes())  + "_" +
    ofToString(ofGetSeconds());

    int task;
    if (current_task == 1)
    {
        task = task1;
        temporaryLog("First task: " + ofToString(task));
    }
    if (current_task == 2)
    {
        task = task2;
        temporaryLog("Second task: " + ofToString(task));
    }
    if (current_task == 3)
    {
        task = task3;
        temporaryLog("Third task: " + ofToString(task));
    }
    if (current_task == 4)
    {
        task = 4;
        temporaryLog("Final task: " + ofToString(task));
    }
    
    std::string filename =
    "user_"     + ofToString(user)      + "-" +
    "sys_"      + ofToString(system)    + "-" +
    "task_"     + ofToString(task)      + "-" +
    "timestamp_"+ timestamp + ".txt";
    
    logFile.open(filename, ofFile::WriteOnly);
}

void Logger::logToFile(std::string mode, float startTime, float endTime, float interval)
{
    logFile << mode << " " << startTime << " " << endTime << " " << interval << std::endl;
}

bool Logger::getIsSystemGrab()
{
    return system == 1;
}

Logger::~Logger(){}