//
//  SpeechProcessor.h
//  airsketcher
//
//  Created by Kevin Wong on 3/20/15.
//
//

#ifndef __airsketcher__SpeechProcessor__
#define __airsketcher__SpeechProcessor__

#include "ofxSpeechRecognizer.h"

class SpeechProcessor
{
public:
    
    SpeechProcessor();
    ~SpeechProcessor();
    
    void setup(const vector<string> &commands);
    
    std::string getLastCommand();
    std::string getStatusMessage();
    
private:
    
    ofxSpeechRecognizer   speechRecognizer;

    std::string lastCommand;
    std::string displayCommand;
    void onSpeechRecognized(std::string& recognizedSentence);
    
    float time;
};


#endif /* defined(__airsketcher__SpeechProcessor__) */
