//
//  SpeechProcessor.cpp
//  airsketcher
//
//  Created by Kevin Wong on 3/20/15.
//
//

#include "SpeechProcessor.h"

SpeechProcessor::SpeechProcessor()
: lastCommand(""), displayCommand(" - - - "), time(ofGetElapsedTimef())
{
    speechRecognizer.initRecognizer();
    speechRecognizer.loadDictionaryFromFile("dictionary.txt");
    
    ofAddListener(speechRecognizer.speechRecognizedEvent, this, &SpeechProcessor::onSpeechRecognized);
    
    speechRecognizer.startListening();
}

SpeechProcessor::~SpeechProcessor()
{
    speechRecognizer.stopListening();
}

std::string SpeechProcessor::getStatusMessage()
{
    if ((ofGetElapsedTimef() - time) > 3)
    {
        displayCommand = " - - - ";
    }
    
    std::stringstream msg;
    msg << "[SPEECH]: ";
    msg << "last command: " << displayCommand << "\n";
    
    return msg.str();
}

std::string SpeechProcessor::getLastCommand()
{
    std::string command = lastCommand;
    lastCommand = "";
    return command;
}

void SpeechProcessor::onSpeechRecognized(std::string &recognizedSentence)
{
    lastCommand = recognizedSentence.substr(9);
    displayCommand = lastCommand;
    time = ofGetElapsedTimef();
}