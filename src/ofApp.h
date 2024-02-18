#pragma once

#include "ofMain.h"
#include "ofxDmx.h"
#include "ofxOsc.h"
#include "Light.hpp"

#define PORT 6000

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofSerial serial;
    vector <ofSerialDeviceInfo> serialDevices;
    char serialOptions[36] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int maxNSerialOptions = 36;
    int dmxDeviceSelection = 0;
    
    int mode = 0;
    int SELECTING = 0;
    int RUNNING = 1;
    
    ofxDmx dmx;
    ofxOscReceiver oscReceive;
    bool gotData = false;
    bool connected = false;
    bool displayMockUp = false;
    bool enableInteraction = false;
    bool displayInfo = true;
    
    int dmxData[512];
    int nValsPerLight = 8;
    
    int nLights = 8;
    int nLightsToShow = 4;
    Light* lights;
    
    bool currentlyChangingType = false;
    int currentlyFocusedLight = 0;
    
    vector<string> arguments;
};
