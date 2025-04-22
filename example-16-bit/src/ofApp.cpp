#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(30);
    
    // Initialize ACN sender - replace with your DMX controller's IP address
    acnSender.setup("192.168.0.50", true); // true = multicast
    
    // Initialize basic settings
    universe = 1;           // Starting universe
    startChannel = 1;       // Starting channel
    useMsbFirst = true;     // MSB first (high byte, then low byte)
    numLeds = 8;            // Number of LEDs in the array
    animationTime = 0.0f;   // Animation timer
    
    // Initialize RGB values array with 3 values per LED (R, G, B)
    // Each color channel is 16-bit (0-65535)
    rgbValues.resize(numLeds * 3, 0);
}

//--------------------------------------------------------------
void ofApp::update(){
    // Update animation time
    animationTime += 0.02;
    
    // Update all RGB values with a simple animation
    for(int i = 0; i < numLeds; i++) {
        int baseIndex = i * 3;
        
        // Create animated colors using sine waves with different phases
        float redPhase = animationTime + (i * 0.3);
        float greenPhase = animationTime * 0.7 + (i * 0.4);
        float bluePhase = animationTime * 0.5 + (i * 0.5);
        
        // Convert to 16-bit values (0-65535)
        rgbValues[baseIndex]     = static_cast<uint16_t>(32767.5 + 32767.5 * sin(redPhase));   // R
        rgbValues[baseIndex + 1] = static_cast<uint16_t>(32767.5 + 32767.5 * sin(greenPhase)); // G
        rgbValues[baseIndex + 2] = static_cast<uint16_t>(32767.5 + 32767.5 * sin(bluePhase));  // B
    }
    
    // Set byte order based on your fixture requirements
    ofxACNSender::ByteOrder byteOrder = useMsbFirst ? 
                                       ofxACNSender::MSB_FIRST : 
                                       ofxACNSender::LSB_FIRST;
    
    // Send the 16-bit RGB values to the LEDs
    // Each 16-bit value takes 2 DMX channels
    acnSender.setChannels16Bit(
        universe,
        startChannel,
        rgbValues.data(),
        rgbValues.size(),
        byteOrder
    );
    
    // Send the packet
    acnSender.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(40);
    
    // Display information
    ofSetColor(255);
    ofDrawBitmapString("16-bit sACN Example: Sending 16-bit RGB values to LED array", 20, 30);
    ofDrawBitmapString("Press SPACE to toggle between MSB_FIRST and LSB_FIRST byte order", 20, 50);
    ofDrawBitmapString("Each LED uses 6 DMX channels (2 channels per 16-bit color component)", 20, 70);
    
    // Display current settings
    string byteOrderText = useMsbFirst ? "MSB_FIRST (high byte, then low byte)" : "LSB_FIRST (low byte, then high byte)";
    ofDrawBitmapString("Current byte order: " + byteOrderText, 20, 100);
    ofDrawBitmapString("Universe: " + ofToString(universe) + ", Start Channel: " + ofToString(startChannel), 20, 120);
    
    // Display LED colors
    ofDrawBitmapString("LED Preview:", 20, 160);
    
    // Draw each LED's color
    for(int i = 0; i < numLeds; i++) {
        int baseIndex = i * 3;
        
        // Get normalized RGB values (0-1) from 16-bit values (0-65535)
        float r = rgbValues[baseIndex] / 65535.0f;
        float g = rgbValues[baseIndex + 1] / 65535.0f;
        float b = rgbValues[baseIndex + 2] / 65535.0f;
        
        // Draw LED
        ofSetColor(r * 255, g * 255, b * 255);
        ofDrawRectangle(20 + (i * 60), 180, 50, 50);
        
        // Draw 16-bit values below each LED
        ofSetColor(255);
        ofDrawBitmapString("R: " + ofToString(rgbValues[baseIndex]), 20 + (i * 60), 260);
        ofDrawBitmapString("G: " + ofToString(rgbValues[baseIndex + 1]), 20 + (i * 60), 280);
        ofDrawBitmapString("B: " + ofToString(rgbValues[baseIndex + 2]), 20 + (i * 60), 300);
    }
    
    // Display channel mapping
    ofDrawBitmapString("Channel Mapping:", 20, 340);
    ofDrawBitmapString("Each 16-bit value uses 2 DMX channels:", 20, 360);
    ofDrawBitmapString("LED 1: CH 1-2 (R), CH 3-4 (G), CH 5-6 (B)", 20, 380);
    ofDrawBitmapString("LED 2: CH 7-8 (R), CH 9-10 (G), CH 11-12 (B)", 20, 400);
    ofDrawBitmapString("And so on...", 20, 420);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ') {
        // Toggle byte order
        useMsbFirst = !useMsbFirst;
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