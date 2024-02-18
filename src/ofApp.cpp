#include <stdlib.h>
#include <stdio.h>
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    serialDevices = serial.getDeviceList();

    if(arguments.size() > 1){
//        for(int i = 0; i < arguments.size(); i++){
//            cout << arguments[i] << "\n";
//        }
        connected = dmx.connect(arguments[1],512);
        dmx.setLevel(1,255);
        mode = RUNNING;
    }
    
    //connected = dmx.connect("tty.usbserial-EN209397",512);
    
    oscReceive.setup(PORT);
    
    ofSetFrameRate(120);
    
    for(int i = 0; i < 512; i++){
        dmxData[i] = 0;
    }
    
    lights = (Light*)calloc(nLights,sizeof(Light));
    
    for(int i = 0; i < nLights; i++){
        lights[i].create(SLIMPAR,i*nValsPerLight);
    }
    
    ofSetBackgroundColor(0);
}

//--------------------------------------------------------------
void ofApp::update(){
    // ========= JUST FOR TESTING ================
    //        for(int i = 2; i < 6; i++){
    //            int level = ofMap(sin(ofGetElapsedTimef() * i),-1.0,1.0,0,255);
    //            //cout << i << ": " << level << endl;
    //            dmx.setLevel(i,level);
    //        }
    
    gotData = false;
    // only update it once every cycle, not every time an osc is received
    while(oscReceive.hasWaitingMessages()){
        //cout << "something received" << endl;
        ofxOscMessage m;
        oscReceive.getNextMessage(&m);
        
        if(m.getAddress() == "/dmx"){
            int chan = m.getArgAsInt(0);
            float val = m.getArgAsInt(1);
            //cout << chan << ": " << val << endl;
            dmx.setLevel(chan, val);
            //dmxData[chan-1] = val;
            dmx.update();
            gotData = true;
        } else if (m.getAddress() == "/dmxAll512"){
            for(int i = 0; i < m.getNumArgs(); i++){
                int val = m.getArgAsInt(i);
                dmxData[i] = val;
                //cout << val << endl;
                dmx.setLevel(i+1,val);
                cout << dmxData[i] << "\n";
            }
            //            dmxData[1] << dmxData[2] << dmxData[3] << dmxData[4] << endl;
            dmx.update();
            gotData = true;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255);
    int yStart = 30;
    ofDrawBitmapString("PORT:"+ofToString(PORT), 10, yStart += 15);
    ofDrawBitmapString("Receiving From SuperCollider (green = true)", 10, yStart += 30);
    if(gotData){
        ofSetColor(0, 255, 0);
    } else {
        ofSetColor(255, 0, 0);
    }
    ofDrawRectangle(10, yStart += 4, 20, 20);
    
    if(mode == SELECTING){
        ofSetColor(255);
        ofDrawBitmapString("CHOOSE DMX DEVICE WITH KEY, THEN HIT SPACEBAR:", 10, yStart += 50);
        
        for(int i = 0; i < serialDevices.size() && i < maxNSerialOptions; i++){
            if(i == dmxDeviceSelection) {ofSetColor(0,255,0);} else {ofSetColor(255);}
            ofDrawBitmapString("("+ofToString(serialOptions[i])+")", 10, yStart += 15);
            ofDrawBitmapString(serialDevices[i].getDeviceName(), 40,yStart);
        }
        
    } else if (mode == RUNNING){
        if(dmx.isConnected()){
            ofSetColor(0,255,0);
            ofDrawBitmapString("DMX CONNECTED TO: ", 10, yStart += 50);
            ofDrawBitmapString(serialDevices[dmxDeviceSelection].getDeviceName(),10,yStart += 15);
        } else {
            ofSetColor(255,0,0);
            ofDrawBitmapString("DMX NOT CONNECTED!", 10, yStart += 50);
        }
    }
}

//--------------------------------------------------------------
void ofApp::exit(){
    dmx.clear();
    dmx.update();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(mode == SELECTING){
        if(key == ' '){
            // make selection and connect to device
            dmx.connect(serialDevices[dmxDeviceSelection].getDeviceName(),512);
            mode = RUNNING;
        } else {
            for(int i = 0; i < serialDevices.size() && i < maxNSerialOptions; i++){
                if(key == serialOptions[i]){
                    dmxDeviceSelection = i;
                }
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
