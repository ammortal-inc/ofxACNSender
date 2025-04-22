#pragma once

#include "ofMain.h"
#include "ofxACNSender.h"

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();

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

        // ACN sender object
        ofxACNSender acnSender;
        
        // Basic settings
        int universe;
        int startChannel;
        bool useMsbFirst;
        
        // 16-bit RGB color values (0-65535 for each component)
        std::vector<uint16_t> rgbValues;
        int numLeds;
        float animationTime;
};