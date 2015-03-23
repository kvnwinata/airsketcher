//
//  HandProcessor.h
//  airsketcher
//
//  Created by Kevin Wong on 3/20/15.
//
//

#ifndef __airsketcher__HandProcessor__
#define __airsketcher__HandProcessor__

#include "LeapHand.h"

class HandProcessor : public Leap::Listener
{
public:
    
    HandProcessor();
    ~HandProcessor();
    
    void update();
    void drawHands();
    
    std::string getStatusMessage();
    
    LeapHand* getHandAtIndex(int i); // 0 or 1
    
private:
    void processCurrentFrame(const Leap::Frame &frame);

    int64_t             lastFrameId;
    virtual void onConnect(const Leap::Controller &controller) override;
    
    Leap::Controller    controller;
    
    vector<LeapHand>    hands;
    
    ofImage             leapImage;

};

#endif /* defined(__airsketcher__HandProcessor__) */
